from utilities import place_random, print_board

DEV_MODE = False


def main(game_board: [[int, ], ]) -> [[int, ], ]:
    """
    2048 main function, runs a game of 2048 in the console.

    Uses the following keys:
    w - shift up
    a - shift left
    s - shift down
    d - shift right
    q - ends the game and returns control of the console
    :param game_board: a 4x4 2D list of integers representing a game of 2048
    :return: returns the ending game board
    """
    
    
    def count_zero(game_board):
        num_zeros = 0
        for r in range(len(game_board)):
                for c in range(len(game_board[r])):
                    if game_board[r][c] == 0:
                        num_zeros += 1
        return num_zeros
    
    def randomegenerator(game_board, same):
        if same != 4:
            num_zeros = count_zero(game_board)
            if num_zeros > 0:
                i = 0
                while i < 1:
                    randomo = place_random(game_board)
                    rowrandom = randomo['row']
                    columnrandom = randomo['column']
                    valuerandom = randomo['value']
                    if game_board[rowrandom][columnrandom] == 0:
                        game_board[rowrandom][columnrandom] = valuerandom
                        i += 1
        return game_board
        
    def winlost(gameover):
        if gameover == True:
            for r in range(len(game_board)):
                for c in range(len(game_board[r])):
                    if game_board[r][c] == 2048:
                        gameover = 'Won'
                        return 'Won'
                        break
        return 'Lost'
        
    def initialize_board(game_board):
        if len(game_board) != 4:
            game_board = ([[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]])
        if len(game_board[0]) != 4:
            game_board[0] = [0, 0, 0, 0]
        if len(game_board[0]) != 4:
            game_board[1] = [0, 0, 0, 0]
        if len(game_board[0]) != 4:
            game_board[2] = [0, 0, 0, 0]
        if len(game_board[0]) != 4:
            game_board[3] = [0, 0, 0, 0]
        return game_board
    
    same = 0
    game_board = initialize_board(game_board)
    gameover = game_over(game_board)
    while gameover == False:
        gameover = game_over(game_board)
        if gameover == True:
            facts = winlost(gameover)
            if facts == 'Won':
                print('Won')
                break
            if facts == 'Lost':
                print('Board is full, no valid moves')
                print('Gameover')
                break
        elif gameover == False:
            if count_zero(game_board) == 16:
                randomegenerator(game_board, same)
            if same != 4:
                print_board(game_board)
                move = input()
            elif same == 4:
                print_board(game_board)
                move = input()
            if len(move) > 1:
                move = input()
            if len(move) == 1:
                if move == 'q' or move == 'Q':
                    print('Goodbye')
                    gameover = 'Yes'
                elif move == 'a' or move == 'A':
                    same = 0
                    for index in range(len(game_board)):
                        if game_board[index][0] == 0:
                            if game_board[index][1] == 0:
                                if game_board[index][2] == 0:
                                    if game_board[index][3] == 0:
                                        game_board[index][3] = 0
                                        same += 1
                                    elif game_board[index][3] != 0:
                                        game_board[index][0] = game_board[index][3]
                                        game_board[index][3] = 0
                                elif game_board[index][2] != 0:
                                    game_board[index][0] = game_board[index][2]
                                    game_board[index][2] = 0
                                    if game_board[index][3] == 0:
                                        game_board[index][3] = 0
                                    elif game_board[index][3] != 0:
                                        if game_board[index][0] == game_board[index][3]:
                                            game_board[index][0] = game_board[index][0] + game_board[index][3]
                                            game_board[index][3] = 0
                                        elif game_board[index][0] != game_board[index][3]:
                                            game_board[index][1] = game_board[index][3]
                                            game_board[index][3] = 0
                            elif game_board[index][1] != 0:
                                game_board[index][0] = game_board[index][1]
                                game_board[index][1] = 0
                                if game_board[index][2] == 0:
                                    if game_board[index][3] == 0:
                                        game_board[index][3] = 0
                                    elif game_board[index][3] != 0:
                                        if game_board[index][0] == game_board[index][3]:
                                            game_board[index][0] = game_board[index][0] + game_board[index][3]
                                            game_board[index][3] = 0
                                        elif game_board[index][0] != game_board[index][3]:
                                            game_board[index][1] = game_board[index][3]
                                            game_board[index][3] = 0
                                elif game_board[index][2] != 0:
                                    if game_board[index][0] == game_board[index][2]:
                                        game_board[index][0] = game_board[index][0] + game_board[index][2]
                                        game_board[index][2] = 0
                                        if game_board[index][3] == 0:
                                            game_board[index][3] = 0
                                        elif game_board[index][3] != 0:
                                            game_board[index][1] = game_board[index][3]
                                            game_board[index][3] = 0
                                    elif game_board[index][0] != game_board[index][2]:
                                        game_board[index][1] = game_board[index][2]
                                        game_board[index][2] = 0
                                        if game_board[index][3] == 0:
                                            game_board[index][3] = 0
                                        elif game_board[index][3] != 0:
                                            if game_board[index][1] == game_board[index][3]:
                                                game_board[index][1] = game_board[index][1] + game_board[index][3]
                                                game_board[index][3] = game_board[index][0]
                                            elif game_board[index][1] != game_board[index][3]:
                                                game_board[index][2] = game_board[index][3]
                                                game_board[index][3] = 0
                        elif game_board[index][0] != 0:
                            if game_board[index][0] == game_board[index][1]:
                                game_board[index][0] = game_board[index][0] + game_board[index][1]
                                game_board[index][1] = 0
                                if game_board[index][2] == 0:
                                    if game_board[index][3] == 0:
                                        game_board[index][3] = game_board[index][3]
                                    elif game_board[index][3] != 0:
                                        game_board[index][1] = game_board[index][3]
                                        game_board[index][3] = 0
                                elif game_board[index][2] != 0:
                                    if game_board[index][2] != 0 and game_board[index][2] == game_board[index][0]:
                                        game_board[index][1] = game_board[index][2]
                                        game_board[index][2] = 0
                                        if game_board[index][3] == 0:
                                            game_board[index][3] = game_board[index][3]
                                        elif game_board[index][3] != 0:
                                            game_board[index][1] = game_board[index][3]
                                            game_board[index][3] = 0
                                    elif game_board[index][2] != 0 and game_board[index][2] == game_board[index][3]:
                                        game_board[index][1] = game_board[index][2] + game_board[index][3]
                                        game_board[index][2] = 0
                                        game_board[index][3] = 0
                                    else:
                                        game_board[index][1] = game_board[index][2]
                                        game_board[index][2] = 0
                                        if game_board[index][3] == 0:
                                            game_board[index][3] = 0
                                        elif game_board[index][3] != 0:
                                            if game_board[index][1] == game_board[index][3]:
                                                game_board[index][1] = game_board[index][1] + game_board[index][3]
                                                game_board[index][3] = game_board[index][0]
                                            elif game_board[index][1] != game_board[index][3]:
                                                game_board[index][2] = game_board[index][3]
                                                game_board[index][3] = 0
                            elif game_board[index][0] != game_board[index][1]:
                                if game_board[index][1] == 0:
                                    if game_board[index][0] == game_board[index][2]:
                                        game_board[index][0] = game_board[index][0] + game_board[index][2]
                                        game_board[index][2] = 0
                                        if game_board[index][3] == 0:
                                            game_board[index][3] = 0
                                            same += 1
                                        elif game_board[index][3] != 0:
                                            game_board[index][1] = game_board[index][3]
                                            game_board[index][3] = 0
                                    elif game_board[index][0] != game_board[index][2]:
                                        if game_board[index][2] == 0:
                                            if game_board[index][3] == 0:
                                                game_board[index][3] = 0
                                                same += 1
                                            elif game_board[index][3] != 0:
                                                if game_board[index][0] == game_board[index][3]:
                                                    game_board[index][0] = game_board[index][0] + game_board[index][3]
                                                    game_board[index][3] = 0
                                                elif game_board[index][0] != game_board[index][3]:
                                                    game_board[index][1] = game_board[index][3]
                                                    game_board[index][3] = 0
                                        elif game_board[index][2] != 0:
                                            game_board[index][1] = game_board[index][2]
                                            game_board[index][2] = 0
                                            if game_board[index][3] == 0:
                                                game_board[index][3] = 0
                                            elif game_board[index][3] != 0:
                                                if game_board[index][1] == game_board[index][3]:
                                                    game_board[index][1] = game_board[index][1] + game_board[index][3]
                                                    game_board[index][3] = 0
                                                elif game_board[index][1] != game_board[index][3]:
                                                    game_board[index][2] = game_board[index][3]
                                                    game_board[index][3] = 0
                                elif game_board[index][1] != 0:
                                    if game_board[index][1] == game_board[index][2]:
                                        game_board[index][1] = game_board[index][1] + game_board[index][2]
                                        game_board[index][2] = 0
                                        if game_board[index][3] == 0:
                                            game_board[index][3] = 0
                                        elif game_board[index][3] != 0:
                                            game_board[index][2] = game_board[index][3]
                                            game_board[index][3] = 0
                                    elif game_board[index][1] != game_board[index][2]:
                                        if game_board[index][2] == 0:
                                            if game_board[index][3] == 0:
                                                game_board[index][3] = 0
                                                same += 1
                                            elif game_board[index][3] != 0:
                                                if game_board[index][1] == game_board[index][3]:
                                                    game_board[index][1] = game_board[index][1] + game_board[index][3]
                                                    game_board[index][3] = 0
                                                elif game_board[index][1] != game_board[index][3]:
                                                    game_board[index][2] = game_board[index][3]
                                                    game_board[index][3] = 0
                                        elif game_board[index][2] != 0:
                                            if game_board[index][3] == 0:
                                                game_board[index][3] = 0
                                                same += 1
                                            elif game_board[index][3] != 0:
                                                if game_board[index][2] == game_board[index][3]:
                                                    game_board[index][2] = game_board[index][2] + game_board[index][3]
                                                    game_board[index][3] = 0
                                                elif game_board[index][2] != game_board[index][3]:
                                                    game_board[index][3] = game_board[index][3]
                                                    same += 1
                    print()
                    randomegenerator(game_board, same)
                elif move == 'd' or move == 'D':
                    same = 0
                    for index in range(len(game_board)):
                        if game_board[index][3] == 0:
                            if game_board[index][2] == 0:
                                if game_board[index][1] == 0:
                                    if game_board[index][0] == 0:
                                        game_board[index][0] = 0
                                        same += 1
                                    elif game_board[index][0] != 0:
                                        game_board[index][3] = game_board[index][0]
                                        game_board[index][0] = 0
                                elif game_board[index][1] != 0:
                                    game_board[index][3] = game_board[index][1]
                                    game_board[index][1] = 0
                                    if game_board[index][0] == 0:
                                        game_board[index][0] = 0
                                    elif game_board[index][0] != 0:
                                        if game_board[index][3] == game_board[index][0]:
                                            game_board[index][3] = game_board[index][3] + game_board[index][0]
                                            game_board[index][0] = 0
                                        elif game_board[index][3] != game_board[index][0]:
                                            game_board[index][2] = game_board[index][0]
                                            game_board[index][0] = 0
                            elif game_board[index][2] != 0:
                                game_board[index][3] = game_board[index][2]
                                game_board[index][2] = 0
                                if game_board[index][1] == 0:
                                    if game_board[index][0] == 0:
                                        game_board[index][0] = 0
                                    elif game_board[index][0] != 0:
                                        if game_board[index][3] == game_board[index][0]:
                                            game_board[index][3] = game_board[index][3] + game_board[index][0]
                                            game_board[index][0] = 0
                                        elif game_board[index][3] != game_board[index][0]:
                                            game_board[index][1] = game_board[index][0]
                                            game_board[index][0] = 0
                                elif game_board[index][1] != 0:
                                    if game_board[index][3] == game_board[index][1]:
                                        game_board[index][3] = game_board[index][3] + game_board[index][1]
                                        game_board[index][1] = 0
                                        if game_board[index][0] == 0:
                                            game_board[index][0] = 0
                                        elif game_board[index][0] != 0:
                                            game_board[index][2] = game_board[index][0]
                                            game_board[index][0] = 0
                                    elif game_board[index][3] != game_board[index][1]:
                                        game_board[index][2] = game_board[index][1]
                                        game_board[index][1] = 0
                                        if game_board[index][0] == 0:
                                            game_board[index][0] = 0
                                        elif game_board[index][0] != 0:
                                            if game_board[index][2] == game_board[index][0]:
                                                game_board[index][2] = game_board[index][2] + game_board[index][0]
                                                game_board[index][0] = game_board[index][3]
                                            elif game_board[index][2] != game_board[index][0]:
                                                game_board[index][1] = game_board[index][0]
                                                game_board[index][0] = 0
                        elif game_board[index][3] != 0:
                            if game_board[index][3] == game_board[index][2]:
                                game_board[index][3] = game_board[index][3] + game_board[index][2]
                                game_board[index][2] = 0
                                if game_board[index][1] == 0:
                                    if game_board[index][0] == 0:
                                        game_board[index][0] = game_board[index][0]
                                    elif game_board[index][0] != 0:
                                        game_board[index][2] = game_board[index][0]
                                        game_board[index][0] = 0
                                elif game_board[index][1] != 0:
                                    if game_board[index][1] != 0 and game_board[index][1] == game_board[index][3]:
                                        game_board[index][2] = game_board[index][1]
                                        game_board[index][1] = 0
                                        if game_board[index][0] == 0:
                                            game_board[index][0] = game_board[index][0]
                                        elif game_board[index][0] != 0:
                                            game_board[index][2] = game_board[index][0]
                                            game_board[index][0] = 0
                                    elif game_board[index][1] != 0 and game_board[index][1] == game_board[index][0]:
                                        game_board[index][2] = game_board[index][1] + game_board[index][0]
                                        game_board[index][1] = 0
                                        game_board[index][0] = 0
                                    else:
                                        game_board[index][2] = game_board[index][1]
                                        game_board[index][1] = 0
                                        if game_board[index][0] == 0:
                                            game_board[index][0] = 0
                                        elif game_board[index][0] != 0:
                                            if game_board[index][2] == game_board[index][0]:
                                                game_board[index][2] = game_board[index][2] + game_board[index][0]
                                                game_board[index][0] = game_board[index][3]
                                            elif game_board[index][2] != game_board[index][0]:
                                                game_board[index][1] = game_board[index][0]
                                                game_board[index][0] = 0
                            elif game_board[index][3] != game_board[index][2]:
                                if game_board[index][2] == 0:
                                    if game_board[index][3] == game_board[index][1]:
                                        game_board[index][3] = game_board[index][3] + game_board[index][1]
                                        game_board[index][1] = 0
                                        if game_board[index][0] == 0:
                                            game_board[index][0] = 0
                                            same += 1
                                        elif game_board[index][0] != 0:
                                            game_board[index][2] = game_board[index][0]
                                            game_board[index][0] = 0
                                    elif game_board[index][3] != game_board[index][1]:
                                        if game_board[index][1] == 0:
                                            if game_board[index][0] == 0:
                                                game_board[index][0] = 0
                                                same += 1
                                            elif game_board[index][0] != 0:
                                                if game_board[index][3] == game_board[index][0]:
                                                    game_board[index][3] = game_board[index][3] + game_board[index][0]
                                                    game_board[index][0] = 0
                                                elif game_board[index][3] != game_board[index][0]:
                                                    game_board[index][2] = game_board[index][0]
                                                    game_board[index][0] = 0
                                        elif game_board[index][1] != 0:
                                            game_board[index][2] = game_board[index][1]
                                            game_board[index][1] = 0
                                            if game_board[index][0] == 0:
                                                game_board[index][0] = 0
                                            elif game_board[index][0] != 0:
                                                if game_board[index][2] == game_board[index][0]:
                                                    game_board[index][2] = game_board[index][2] + game_board[index][0]
                                                    game_board[index][0] = 0
                                                elif game_board[index][2] != game_board[index][0]:
                                                    game_board[index][1] = game_board[index][0]
                                                    game_board[index][0] = 0
                                elif game_board[index][2] != 0:
                                    if game_board[index][2] == game_board[index][1]:
                                        game_board[index][2] = game_board[index][2] + game_board[index][1]
                                        game_board[index][1] = 0
                                        if game_board[index][0] == 0:
                                            game_board[index][0] = 0
                                        elif game_board[index][0] != 0:
                                            game_board[index][1] = game_board[index][0]
                                            game_board[index][0] = 0
                                    elif game_board[index][2] != game_board[index][1]:
                                        if game_board[index][1] == 0:
                                            if game_board[index][0] == 0:
                                                game_board[index][0] = 0
                                                same += 1
                                            elif game_board[index][0] != 0:
                                                if game_board[index][2] == game_board[index][0]:
                                                    game_board[index][2] = game_board[index][2] + game_board[index][0]
                                                    game_board[index][0] = 0
                                                elif game_board[index][2] != game_board[index][0]:
                                                    game_board[index][1] = game_board[index][0]
                                                    game_board[index][0] = 0
                                        elif game_board[index][1] != 0:
                                            if game_board[index][0] == 0:
                                                game_board[index][0] = 0
                                                same += 1
                                            elif game_board[index][0] != 0:
                                                if game_board[index][1] == game_board[index][0]:
                                                    game_board[index][1] = game_board[index][1] + game_board[index][0]
                                                    game_board[index][0] = 0
                                                elif game_board[index][1] != game_board[index][0]:
                                                    game_board[index][0] = game_board[index][0]
                                                    same += 1
                    print()
                    randomegenerator(game_board, same)
                elif move == 'w' or move == 'W':
                    same = 0
                    for index in range(len(game_board)):
                        if game_board[0][index] == 0:
                            if game_board[1][index] == 0:
                                if game_board[2][index] == 0:
                                    if game_board[3][index] == 0:
                                        game_board[3][index] = 0
                                        same += 1
                                    elif game_board[3][index] != 0:
                                        game_board[0][index] = game_board[3][index]
                                        game_board[3][index] = 0
                                elif game_board[2][index] != 0:
                                    game_board[0][index] = game_board[2][index]
                                    game_board[2][index] = 0
                                    if game_board[3][index] == 0:
                                        game_board[3][index] = 0
                                    elif game_board[3][index] != 0:
                                        if game_board[0][index] == game_board[3][index]:
                                            game_board[0][index] = game_board[0][index] + game_board[3][index]
                                            game_board[3][index] = 0
                                        elif game_board[0][index] != game_board[3][index]:
                                            game_board[1][index] = game_board[3][index]
                                            game_board[3][index] = 0
                            elif game_board[1][index] != 0:
                                game_board[0][index] = game_board[1][index]
                                game_board[1][index] = 0
                                if game_board[2][index] == 0:
                                    if game_board[3][index] == 0:
                                        game_board[3][index] = 0
                                    elif game_board[3][index] != 0:
                                        if game_board[0][index] == game_board[3][index]:
                                            game_board[0][index] = game_board[0][index] + game_board[3][index]
                                            game_board[3][index] = 0
                                        elif game_board[0][index] != game_board[3][index]:
                                            game_board[1][index] = game_board[3][index]
                                            game_board[3][index] = 0
                                elif game_board[2][index] != 0:
                                    if game_board[0][index] == game_board[2][index]:
                                        game_board[0][index] = game_board[0][index] + game_board[2][index]
                                        game_board[2][index] = 0
                                        if game_board[3][index] == 0:
                                            game_board[3][index] = 0
                                        elif game_board[3][index] != 0:
                                            game_board[1][index] = game_board[3][index]
                                            game_board[3][index] = 0
                                    elif game_board[0][index] != game_board[2][index]:
                                        game_board[1][index] = game_board[2][index]
                                        game_board[2][index] = 0
                                        if game_board[3][index] == 0:
                                            game_board[3][index] = 0
                                        elif game_board[3][index] != 0:
                                            if game_board[1][index] == game_board[3][index]:
                                                game_board[1][index] = game_board[1][index] + game_board[3][index]
                                                game_board[3][index] = game_board[0][index]
                                            elif game_board[1][index] != game_board[3][index]:
                                                game_board[2][index] = game_board[3][index]
                                                game_board[3][index] = 0
                        elif game_board[0][index] != 0:
                            if game_board[0][index] == game_board[1][index]:
                                game_board[0][index] = game_board[0][index] + game_board[1][index]
                                game_board[1][index] = 0
                                if game_board[2][index] == 0:
                                    if game_board[3][index] == 0:
                                        game_board[3][index] = game_board[3][index]
                                    elif game_board[3][index] != 0:
                                        game_board[1][index] = game_board[3][index]
                                        game_board[3][index] = 0
                                elif game_board[2][index] != 0:
                                    if game_board[2][index] != 0 and game_board[2][index] == game_board[0][index]:
                                        game_board[1][index] = game_board[2][index]
                                        game_board[2][index] = 0
                                        if game_board[3][index] == 0:
                                            game_board[3][index] = game_board[3][index]
                                        elif game_board[3][index] != 0:
                                            game_board[1][index] = game_board[3][index]
                                            game_board[3][index] = 0
                                    elif game_board[2][index] != 0 and game_board[2][index] == game_board[3][index]:
                                        game_board[1][index] = game_board[2][index] + game_board[3][index]
                                        game_board[2][index] = 0
                                        game_board[3][index] = 0
                                    else:
                                        game_board[1][index] = game_board[2][index]
                                        game_board[2][index] = 0
                                        if game_board[3][index] == 0:
                                            game_board[3][index] = 0
                                        elif game_board[3][index] != 0:
                                            if game_board[1][index] == game_board[3][index]:
                                                game_board[1][index] = game_board[1][index] + game_board[3][index]
                                                game_board[3][index] = game_board[0][index]
                                            elif game_board[1][index] != game_board[3][index]:
                                                game_board[2][index] = game_board[3][index]
                                                game_board[3][index] = 0
                            elif game_board[0][index] != game_board[1][index]:
                                if game_board[1][index] == 0:
                                    if game_board[0][index] == game_board[2][index]:
                                        game_board[0][index] = game_board[0][index] + game_board[2][index]
                                        game_board[2][index] = 0
                                        if game_board[3][index] == 0:
                                            game_board[3][index] = 0
                                            same += 1
                                        elif game_board[3][index] != 0:
                                            game_board[1][index] = game_board[3][index]
                                            game_board[3][index] = 0
                                    elif game_board[0][index] != game_board[2][index]:
                                        if game_board[2][index] == 0:
                                            if game_board[3][index] == 0:
                                                game_board[3][index] = 0
                                                same += 1
                                            elif game_board[3][index] != 0:
                                                if game_board[0][index] == game_board[3][index]:
                                                    game_board[0][index] = game_board[0][index] + game_board[3][index]
                                                    game_board[3][index] = 0
                                                elif game_board[0][index] != game_board[3][index]:
                                                    game_board[1][index] = game_board[3][index]
                                                    game_board[3][index] = 0
                                        elif game_board[2][index] != 0:
                                            game_board[1][index] = game_board[2][index]
                                            game_board[2][index] = 0
                                            if game_board[3][index] == 0:
                                                game_board[3][index] = 0
                                            elif game_board[3][index] != 0:
                                                if game_board[1][index] == game_board[3][index]:
                                                    game_board[1][index] = game_board[1][index] + game_board[3][index]
                                                    game_board[3][index] = 0
                                                elif game_board[1][index] != game_board[3][index]:
                                                    game_board[2][index] = game_board[3][index]
                                                    game_board[3][index] = 0
                                elif game_board[1][index] != 0:
                                    if game_board[1][index] == game_board[2][index]:
                                        game_board[1][index] = game_board[1][index] + game_board[2][index]
                                        game_board[2][index] = 0
                                        if game_board[3][index] == 0:
                                            game_board[3][index] = 0
                                        elif game_board[3][index] != 0:
                                            game_board[2][index] = game_board[3][index]
                                            game_board[3][index] = 0
                                    elif game_board[1][index] != game_board[2][index]:
                                        if game_board[2][index] == 0:
                                            if game_board[3][index] == 0:
                                                game_board[3][index] = 0
                                                same += 1
                                            elif game_board[3][index] != 0:
                                                if game_board[1][index] == game_board[3][index]:
                                                    game_board[1][index] = game_board[1][index] + game_board[3][index]
                                                    game_board[3][index] = 0
                                                elif game_board[1][index] != game_board[3][index]:
                                                    game_board[2][index] = game_board[3][index]
                                                    game_board[3][index] = 0
                                        elif game_board[2][index] != 0:
                                            if game_board[3][index] == 0:
                                                game_board[3][index] = 0
                                                same += 1
                                            elif game_board[3][index] != 0:
                                                if game_board[2][index] == game_board[3][index]:
                                                    game_board[2][index] = game_board[2][index] + game_board[3][index]
                                                    game_board[3][index] = 0
                                                elif game_board[2][index] != game_board[3][index]:
                                                    game_board[3][index] = game_board[3][index]
                                                    same += 1
                    print()
                    randomegenerator(game_board, same)
                elif move == 's' or move == 'S':
                    same = 0
                    for index in range(len(game_board)):
                        if game_board[3][index] == 0:
                            if game_board[2][index] == 0:
                                if game_board[1][index] == 0:
                                    if game_board[0][index] == 0:
                                        game_board[0][index] = 0
                                        same += 1
                                    elif game_board[0][index] != 0:
                                        game_board[3][index] = game_board[0][index]
                                        game_board[0][index] = 0
                                elif game_board[1][index] != 0:
                                    game_board[3][index] = game_board[1][index]
                                    game_board[1][index] = 0
                                    if game_board[0][index] == 0:
                                        game_board[0][index] = 0
                                    elif game_board[0][index] != 0:
                                        if game_board[3][index] == game_board[0][index]:
                                            game_board[3][index] = game_board[3][index] + game_board[0][index]
                                            game_board[0][index] = 0
                                        elif game_board[3][index] != game_board[0][index]:
                                            game_board[2][index] = game_board[0][index]
                                            game_board[0][index] = 0
                            elif game_board[2][index] != 0:
                                game_board[3][index] = game_board[2][index]
                                game_board[2][index] = 0
                                if game_board[1][index] == 0:
                                    if game_board[0][index] == 0:
                                        game_board[0][index] = 0
                                    elif game_board[0][index] != 0:
                                        if game_board[3][index] == game_board[0][index]:
                                            game_board[3][index] = game_board[3][index] + game_board[0][index]
                                            game_board[0][index] = 0
                                        elif game_board[3][index] != game_board[0][index]:
                                            game_board[1][index] = game_board[0][index]
                                            game_board[0][index] = 0
                                elif game_board[1][index] != 0:
                                    if game_board[3][index] == game_board[1][index]:
                                        game_board[3][index] = game_board[3][index] + game_board[1][index]
                                        game_board[1][index] = 0
                                        if game_board[0][index] == 0:
                                            game_board[0][index] = 0
                                        elif game_board[0][index] != 0:
                                            game_board[2][index] = game_board[0][index]
                                            game_board[0][index] = 0
                                    elif game_board[3][index] != game_board[1][index]:
                                        game_board[2][index] = game_board[1][index]
                                        game_board[1][index] = 0
                                        if game_board[0][index] == 0:
                                            game_board[0][index] = 0
                                        elif game_board[0][index] != 0:
                                            if game_board[2][index] == game_board[0][index]:
                                                game_board[2][index] = game_board[2][index] + game_board[0][index]
                                                game_board[0][index] = game_board[3][index]
                                            elif game_board[2][index] != game_board[0][index]:
                                                game_board[1][index] = game_board[0][index]
                                                game_board[0][index] = 0
                        elif game_board[3][index] != 0:
                            if game_board[3][index] == game_board[2][index]:
                                game_board[3][index] = game_board[3][index] + game_board[2][index]
                                game_board[2][index] = 0
                                if game_board[1][index] == 0:
                                    if game_board[0][index] == 0:
                                        game_board[0][index] = game_board[0][index]
                                    elif game_board[0][index] != 0:
                                        game_board[2][index] = game_board[0][index]
                                        game_board[0][index] = 0
                                elif game_board[1][index] != 0:
                                    if game_board[1][index] != 0 and game_board[1][index] == game_board[3][index]:
                                        game_board[2][index] = game_board[1][index]
                                        game_board[1][index] = 0
                                        if game_board[0][index] == 0:
                                            game_board[0][index] = game_board[0][index]
                                        elif game_board[0][index] != 0:
                                            game_board[2][index] = game_board[0][index]
                                            game_board[0][index] = 0
                                    elif game_board[1][index] != 0 and game_board[1][index] == game_board[0][index]:
                                        game_board[2][index] = game_board[1][index] + game_board[0][index]
                                        game_board[1][index] = 0
                                        game_board[0][index] = 0
                                    else:
                                        game_board[2][index] = game_board[1][index]
                                        game_board[1][index] = 0
                                        if game_board[0][index] == 0:
                                            game_board[0][index] = 0
                                        elif game_board[0][index] != 0:
                                            if game_board[2][index] == game_board[0][index]:
                                                game_board[2][index] = game_board[2][index] + game_board[0][index]
                                                game_board[0][index] = game_board[3][index]
                                            elif game_board[2][index] != game_board[0][index]:
                                                game_board[1][index] = game_board[0][index]
                                                game_board[0][index] = 0
                            elif game_board[3][index] != game_board[2][index]:
                                if game_board[2][index] == 0:
                                    if game_board[3][index] == game_board[1][index]:
                                        game_board[3][index] = game_board[3][index] + game_board[1][index]
                                        game_board[1][index] = 0
                                        if game_board[0][index] == 0:
                                            game_board[0][index] = 0
                                            same += 1
                                        elif game_board[0][index] != 0:
                                            game_board[2][index] = game_board[0][index]
                                            game_board[0][index] = 0
                                    elif game_board[3][index] != game_board[1][index]:
                                        if game_board[1][index] == 0:
                                            if game_board[0][index] == 0:
                                                game_board[0][index] = 0
                                                same += 1
                                            elif game_board[0][index] != 0:
                                                if game_board[3][index] == game_board[0][index]:
                                                    game_board[3][index] = game_board[3][index] + game_board[0][index]
                                                    game_board[0][index] = 0
                                                elif game_board[3][index] != game_board[0][index]:
                                                    game_board[2][index] = game_board[0][index]
                                                    game_board[0][index] = 0
                                        elif game_board[1][index] != 0:
                                            game_board[2][index] = game_board[1][index]
                                            game_board[1][index] = 0
                                            if game_board[0][index] == 0:
                                                game_board[0][index] = 0
                                            elif game_board[0][index] != 0:
                                                if game_board[2][index] == game_board[0][index]:
                                                    game_board[2][index] = game_board[2][index] + game_board[0][index]
                                                    game_board[0][index] = 0
                                                elif game_board[2][index] != game_board[0][index]:
                                                    game_board[1][index] = game_board[0][index]
                                                    game_board[0][index] = 0
                                elif game_board[2][index] != 0:
                                    if game_board[2][index] == game_board[1][index]:
                                        game_board[2][index] = game_board[2][index] + game_board[1][index]
                                        game_board[1][index] = 0
                                        if game_board[0][index] == 0:
                                            game_board[0][index] = 0
                                        elif game_board[0][index] != 0:
                                            game_board[1][index] = game_board[0][index]
                                            game_board[0][index] = 0
                                    elif game_board[2][index] != game_board[1][index]:
                                        if game_board[1][index] == 0:
                                            if game_board[0][index] == 0:
                                                game_board[0][index] = 0
                                                same += 1
                                            elif game_board[0][index] != 0:
                                                if game_board[2][index] == game_board[0][index]:
                                                    game_board[2][index] = game_board[2][index] + game_board[0][index]
                                                    game_board[0][index] = 0
                                                elif game_board[2][index] != game_board[0][index]:
                                                    game_board[1][index] = game_board[0][index]
                                                    game_board[0][index] = 0
                                        elif game_board[1][index] != 0:
                                            if game_board[0][index] == 0:
                                                game_board[0][index] = 0
                                                same += 1
                                            elif game_board[0][index] != 0:
                                                if game_board[1][index] == game_board[0][index]:
                                                    game_board[1][index] = game_board[1][index] + game_board[0][index]
                                                    game_board[0][index] = 0
                                                elif game_board[1][index] != game_board[0][index]:
                                                    game_board[0][index] = game_board[0][index]
                                                    same += 1
                    print()
                    randomegenerator(game_board, same)

    return game_board
        
def game_over(game_board: [[int, ], ]) -> bool:
    gameover = False
    different = 0
    for r in range(len(game_board)):    
        for c in range(len(game_board[r])):
            if game_board[r][c] == 2048:
                gameover = True
                print(gameover)
                return gameover
                break
    for r in range(len(game_board)):    
        for c in range(len(game_board[r])):
            if game_board[r][c] == 0:
                gameover = False
                return gameover
                break
            elif game_board[r][c] != 0:
                if c < 3:
                    if game_board[r][c] != game_board[r][c+1]:
                        different += 1
    if different == 12:
        different = 0
        for c in range(4):
            for r in range(3):
                if game_board[r][c] != game_board[r+1][c]:
                    different += 1
                    if different == 12:
                        gameover = True
                        return gameover
                        break
    return gameover

if __name__ == "__main__":
    main([[0, 0, 0, 0],
          [0, 0, 0, 0],
          [0, 0, 0, 0],
          [0, 0, 0, 0]])
          