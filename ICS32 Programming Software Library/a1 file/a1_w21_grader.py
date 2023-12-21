# a1_validitychecker.py
#
# ICS 32 Winter 2021
# Assignment #1: File Explorer Grading Tool
#
# NOTE: Heavily adapted from project1_sanitychecker.py written by Alex Thornton.
#


import datetime
import locale
import pathlib
import queue
import subprocess
import sys
import threading
import time
import traceback
import typing



class TextProcessReadTimeout(Exception):
    pass



class TextProcess:
    _READ_INTERVAL_IN_SECONDS = 0.025


    def __init__(self, args: [str], working_directory: str):
        self._process = subprocess.Popen(
            args, cwd = working_directory, bufsize = 0,
            stdin = subprocess.PIPE, stdout = subprocess.PIPE,
            stderr = subprocess.STDOUT)

        self._stdout_read_trigger = queue.Queue()
        self._stdout_buffer = queue.Queue()

        self._stdout_thread = threading.Thread(
            target = self._stdout_read_loop, daemon = True)

        self._stdout_thread.start()


    def __enter__(self):
        return self


    def __exit__(self, tr, exc, val):
        self.close()


    def close(self):
        self._stdout_read_trigger.put('stop')
        self._process.terminate()
        self._process.wait()
        self._process.stdout.close()
        self._process.stdin.close()


    def write_line(self, line: str) -> None:
        try:
            self._process.stdin.write((line + '\n').encode(locale.getpreferredencoding(False)))
            self._process.stdin.flush()

        except OSError:
            pass

    def read_line(self, timeout: float = None) -> str or None:
        self._stdout_read_trigger.put('read')
        
        sleep_time = 0
        
        while timeout == None or sleep_time < timeout:
            try:
                next_result = self._stdout_buffer.get_nowait()

                if next_result == None:
                    return None
                elif isinstance(next_result, Exception):
                    raise next_result
                else:
                    line = next_result.decode(locale.getpreferredencoding(False))

                    if line.endswith('\r\n'):
                        line = line[:-2]
                    elif line.endswith('\n'):
                        line = line[:-1]

                    return line

            except queue.Empty:
                time.sleep(TextProcess._READ_INTERVAL_IN_SECONDS)
                sleep_time += TextProcess._READ_INTERVAL_IN_SECONDS

        raise TextProcessReadTimeout()


    def _stdout_read_loop(self):
        try:
            while self._process.returncode == None:
                if self._stdout_read_trigger.get() == 'read':
                    line = self._process.stdout.readline()

                    if line == b'':
                        self._stdout_buffer.put(None)
                    else:
                        self._stdout_buffer.put(line)
                else:
                    break

        except Exception as e:
            self._stdout_buffer.put(e)



class TestFailure(Exception):
    pass



class TestInputLine:
    def __init__(self, text: str):
        self._text = text

    
    def execute(self, process: TextProcess) -> None:
        try:
            process.write_line(self._text)

        except Exception:
            print_labeled_output(
                'EXCEPTION',
                *[tb_line.rstrip() for tb_line in traceback.format_exc().split('\n')])

            raise TestFailure()

        print_labeled_output('INPUT', self._text)



class TestOutputLine:
    def __init__(self, text: str, timeout_in_seconds: float):
        self._text = text
        self._timeout_in_seconds = timeout_in_seconds


    def execute(self, process: TextProcess) -> None:
        try:
            output_line = process.read_line(self._timeout_in_seconds)

        except TextProcessReadTimeout:
            output_line = None

        except Exception as e:
            print_labeled_output(
                'EXCEPTION',
                *[tb_line.rstrip() for tb_line in traceback.format_exc().split('\n')])

            raise TestFailure()

        if output_line != None:
            if output_line.endswith('\r\n'):
                output_line = output_line[:-2]
            elif output_line.endswith('\n'):
                output_line = output_line[:-1]

            print_labeled_output('OUTPUT', output_line)

            if output_line != self._text:
                print_labeled_output('EXPECTED', self._text)

                index = min(len(output_line), len(self._text))

                for i in range(min(len(output_line), len(self._text))):
                    if output_line[i] != self._text[i]:
                        index = i
                        break

                print_labeled_output('', (' ' * index) + '^')

                print_labeled_output(
                    'ERROR',
                    'This line of output did not match what was expected.  The first',
                    'incorrect character is marked with a ^ above.',
                    '(If you don\'t see a difference, perhaps your program printed',
                    'extra whitespace on the end of this line.)')

                raise TestFailure()

        else:
            print_labeled_output('EXPECTED', self._text)

            print_labeled_output(
                'ERROR',
                'This line of output was expected, but the program did not generate',
                'any additional output after waiting for {} second(s).'.format(self._timeout_in_seconds))

            raise TestFailure()



class TestEndOfOutput:
    def __init__(self, timeout_in_seconds: float):
        self._timeout_in_seconds = timeout_in_seconds


    def execute(self, process: TextProcess) -> None:
        output_line = process.read_line(self._timeout_in_seconds)

        if output_line != None:
            print_labeled_output('OUTPUT', output_line)

            print_labeled_output(
                'ERROR',
                'Extra output was printed after the program should not have generated',
                'any additional output')

            raise TestFailure()



def write_test_file(dir_path: pathlib.Path, sub_path: pathlib.Path, lines: [str]) -> None:
    path = dir_path / sub_path

    if not path.parent.exists():
        path.parent.mkdir(parents = True)

    with path.open('w') as test_file:
        for line in lines:
            test_file.write(line + '\n')



TEST_FILES = [
    (pathlib.Path('test1.txt'), [
        'This is a line of text'
    ]),
    (pathlib.Path('test2.txt'), [
        'There are a few lines of text',
        'in this file',
        'instead of just a couple',
        'of them'
    ]),
    (pathlib.Path('Sub/test1.txt'), [
        'I am Bar',
        'and it is all about me',
        'and everything is about me',
        'so everyone should be focused on me'
    ]),
    (pathlib.Path('Sub/test2.txt'), [
        'Hello, my name is Foo',
        'How are you today?'
    ]),
    (pathlib.Path('Sub/test3.txt'), [
        'Or maybe it should be about you',
        'I cannot decide'
    ]),
    (pathlib.Path('Zzz/read.dsu'), [
        'This is a line of text'
    ]),
    (pathlib.Path('Zzz/zzz.py'), [
        'print(\'Sleep...\')',
        'for i in range(10):',
        '    print(\'ZZZZZZZZZZ\')'
    ])
]

def create_test_directory() -> pathlib.Path:
    now = datetime.datetime.now()

    test_directory_name = 'a1_test_{:04}-{:02}-{:02}-{:02}-{:02}-{:02}'.format(
        now.year, now.month, now.day, now.hour, now.minute, now.second)
    
    test_directory_path = pathlib.Path.cwd() / pathlib.Path(test_directory_name)
    test_directory_path.mkdir(parents = True)

    for sub_path, lines in TEST_FILES:
        write_test_file(test_directory_path, sub_path, lines)

    return test_directory_path

def make_L_test_lines(test_directory_path: pathlib.Path) -> ['TestLine']:
    test_lines = []
    test_lines.append(TestInputLine(
        'L {}'.format(str(test_directory_path))))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('test1.txt')), 10.0))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('test2.txt')), 10.0))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Sub')), 10.0))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Zzz')), 10.0))
    
    return test_lines

def make_Lr_test_lines(test_directory_path: pathlib.Path) -> ['TestLine']:
    test_lines = []
    test_lines.append(TestInputLine(
        'L {} -r'.format(str(test_directory_path))))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('test1.txt')), 10.0))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('test2.txt')), 10.0))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Sub')), 10.0))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Sub/test1.txt')), 10.0))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Sub/test2.txt')), 10.0))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Sub/test3.txt')), 10.0))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Zzz')), 10.0))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Zzz/read.dsu')), 10.0))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Zzz/zzz.py')), 10.0))
    return test_lines

def make_Lf_test_lines(test_directory_path: pathlib.Path) -> ['TestLine']:
    test_lines = []
    test_lines.append(TestInputLine(
        'L {} -f'.format(str(test_directory_path))))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('test1.txt')), 10.0))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('test2.txt')), 10.0))
    return test_lines

def make_Lrf_test_lines(test_directory_path: pathlib.Path) -> ['TestLine']:
    test_lines = []
    test_lines.append(TestInputLine(
        'L {} -r -f'.format(str(test_directory_path))))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('test1.txt')), 10.0))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('test2.txt')), 10.0))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Sub/test1.txt')), 10.0))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Sub/test2.txt')), 10.0))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Sub/test3.txt')), 10.0))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Zzz/read.dsu')), 10.0))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Zzz/zzz.py')), 10.0))
    return test_lines

def make_Lre_test_lines(test_directory_path: pathlib.Path) -> ['TestLine']:
    test_lines = []
    test_lines.append(TestInputLine(
        'L {} -r -e py'.format(str(test_directory_path))))

    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Zzz/zzz.py')), 10.0))
    return test_lines
    
def make_Ls_test_lines(test_directory_path: pathlib.Path) -> ['TestLine']:
    test_lines = []
    test_lines.append(TestInputLine(
        'L {} -s test1.txt'.format(str(test_directory_path))))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('test1.txt')), 10.0))
    return test_lines

def make_Lrs_test_lines(test_directory_path: pathlib.Path) -> ['TestLine']:
    test_lines = []
    test_lines.append(TestInputLine(
        'L {} -r -s test1.txt'.format(str(test_directory_path))))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('test1.txt')), 10.0))
    
    test_lines.append(TestOutputLine(
        str(test_directory_path / pathlib.Path('Sub/test1.txt')), 10.0))
    return test_lines
    
def make_R_test_lines(test_directory_path: pathlib.Path) -> ['TestLine']:
    test_lines = []
    test_lines.append(TestInputLine('R ' +
        str(test_directory_path / 'test1.txt')))
    
    test_lines.append(TestOutputLine('ERROR', 1.0))
    
    test_lines.append(TestInputLine('R ' +
        str(test_directory_path / 'Zzz/read.dsu')))
    
    test_lines.append(TestOutputLine('This is a line of text', 10.0))
    return test_lines

def make_C_test_lines(test_directory_path: pathlib.Path) -> ['TestLine']:
    test_lines = []
    test_lines.append(TestInputLine('C'))
    test_lines.append(TestOutputLine('ERROR', 1.0))
   
    test_lines.append(TestInputLine(
        'C {} -n test3'.format(str(test_directory_path))))
   
    test_lines.append(TestOutputLine(
        str(test_directory_path / 'test3.dsu'), 10.0))
    return test_lines

def make_D_test_lines(test_directory_path: pathlib.Path) -> ['TestLine']:
    test_lines = []
    test_lines.append(TestInputLine('D'))
    test_lines.append(TestOutputLine('ERROR', 1.0))
    test_lines.append(TestInputLine('D ' +
        str(test_directory_path / 'test3.dsu')))
    test_lines.append(TestOutputLine(
        str(test_directory_path / 'test3.dsu DELETED'), 10.0))
    
    return test_lines

def run_grader() -> None:
    test_directory_path = create_test_directory()
    process = None
    tested = []
    pts_total = 0

    while True:
        test = ''
        try:
            process = start_process()

            test = 'L'
            if test not in tested:
                tested.append(test)
                test_lines = make_L_test_lines(test_directory_path)
                run_test_lines(process, test_lines)
                pts_total += 1
                print_labeled_output('{} pts - PASSED {}'.format(1,test))
            
            test = 'Lf'
            if test not in tested:
                tested.append(test)
                test_lines = make_Lf_test_lines(test_directory_path)
                run_test_lines(process, test_lines)
                pts_total += 0.5
                print_labeled_output('{} pts - PASSED {}'.format(0.5,test))
            
            test = 'Lr'
            if test not in tested:
                tested.append(test)
                test_lines = make_Lr_test_lines(test_directory_path)
                run_test_lines(process, test_lines)
                pts_total += 1.5
                print_labeled_output('{} pts - PASSED {}'.format(1.5,test))
            
            test = 'Lrf'
            if test not in tested:
                tested.append(test)
                test_lines = make_Lrf_test_lines(test_directory_path)
                run_test_lines(process, test_lines)
                pts_total += 0.5
                print_labeled_output('{} pts - PASSED {}'.format(0.5,test))
            
            test = 'Lre'
            if test not in tested:
                tested.append(test)
                test_lines = make_Lre_test_lines(test_directory_path)
                run_test_lines(process, test_lines)
                pts_total += 0.5
                print_labeled_output('{} pts - PASSED {}'.format(0.5,test))
            
            test = 'Ls'
            if test not in tested:
                tested.append(test)
                test_lines = make_Ls_test_lines(test_directory_path)
                run_test_lines(process, test_lines)
                pts_total += 0.5
                print_labeled_output('{} pts - PASSED {}'.format(0.5,test))
            
            test = 'Lrs'
            if test not in tested:
                tested.append(test)
                test_lines = make_Lrs_test_lines(test_directory_path)
                run_test_lines(process, test_lines)
                pts_total += 0.5
                print_labeled_output('{} pts - PASSED {}'.format(0.5,test))
            
            test = 'R'
            if test not in tested:
                tested.append(test)
                test_lines = make_R_test_lines(test_directory_path)
                run_test_lines(process, test_lines)
                pts_total += 1
                print_labeled_output('{} pts - PASSED {}'.format(1,test))
            
            test = 'C'
            if test not in tested:
                tested.append(test)
                test_lines = make_C_test_lines(test_directory_path)
                run_test_lines(process, test_lines)
                pts_total += 1
                print_labeled_output('{} pts - PASSED {}'.format(1,test))
            
            test = 'D'
            if test not in tested:
                tested.append(test)
                test_lines = make_D_test_lines(test_directory_path)
                run_test_lines(process, test_lines)
                pts_total += 1
                print_labeled_output('{} pts - PASSED {}'.format(1,test))
            
            break

        except TestFailure:
            print_labeled_output('{} pts - FAILED {}'.format(0,test))

    
    if process != None:
        process.close()

    print('\n')
    print('{}/8 Total points for Requirements and Function.'.format(pts_total))
    print('Review code for design and documentation and assign up to 2 additional pts')
    print('\n')

    return pts_total

def start_process() -> TextProcess:
    filenames_in_dir = [p.name for p in list(pathlib.Path.cwd().iterdir()) if p.is_file()]

    if not 'a1.py' in filenames_in_dir:
        print_labeled_output(
            'ERROR',
            'Cannot find file "a1.py" in this directory.',
            'Make sure that the validity checker is in the same directory as the',
            '"a1.py" that comprises your Assignment #1 solution.  Also, be',
            'sure that you\'ve named your "a1.py" file correctly, noting',
            'that capitalization and spacing matter.')

        raise TestFailure()

    else:
        return TextProcess(
            [sys.executable, str(pathlib.Path.cwd() / 'a1.py')],
            str(pathlib.Path.cwd()))



def print_labeled_output(label: str, *msg_lines: typing.Iterable[str]) -> None:
    showed_first = False

    for msg_line in msg_lines:
        if not showed_first:
            print('{:10}|{}'.format(label, msg_line))
            showed_first = True
        else:
            print('{:10}|{}'.format(' ', msg_line))

    if not showed_first:
        print(label)



def run_test_lines(process: TextProcess, test_lines: 'TestLine') -> None:
    for line in test_lines:
        line.execute(process)



if __name__ == '__main__':
    run_grader()
