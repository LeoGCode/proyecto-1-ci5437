import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print('Usage: python3 n-puzzle-generator.py n')
        print('n is the number of tiles')
        sys.exit(1)

    # generator for the n-puzzle for the given size
    # in the psnv language
    n = int(sys.argv[1])

    # get size of the square
    size = int((n + 1)**(1/2))
    # check if the size is a perfect square
    if size**2 != n + 1:
        print('n is not a perfect square')
        sys.exit(1)

    with open(f'{n}-puzzle.psvn', 'w') as f:
        f.write(f'DOMAIN tile {n+1}\n')
        f.write(f'       b')
        for i in range(1, n+1):
            f.write(f' {i}')
        f.write('\n\n')
        f.write(f'{n+1}\n\n')
        for i in range(n+1):
            f.write(f'tile ')
        f.write('\n\n')
        # generate all the possible s
        # a state is in the form of
        # b X - - - - - - - - - - - - - - =>
        # X b - - - - - - - - - - - - - -
        # b is the blank tile, X is a tile number and - is any other tile
        # first we generate all horizontal moves
        states1 = [f'{i*"- "}b X{(size-2-i)*" -"}' for i in range(size-1)]
        states2 = [f'{i*"- "}X b{(size-2-i)*" -"}' for i in range(size-1)]
        empty = (size - 1)*'- ' + '-'
        for base_state1, base_state2 in zip(states1, states2):
            for i in range(size):
                tmp_state1 = i*f'{empty} ' + \
                    base_state1 + (size-1-i)*f' {empty}'
                tmp_state2 = i*f'{empty} ' + \
                    base_state2 + (size-1-i)*f' {empty}'
                f.write(tmp_state1 + ' => ')
                f.write(tmp_state2 + '\n')
                f.write(tmp_state2 + ' => ')
                f.write(tmp_state1 + '\n')

        # now we generate states of the form
        # b - - - X - - - - - - - - - - - =>
        # X - - - b - - - - - - - - - - -
        # empty_1 = (size - 2)*'- ' + '-'
        states1 = [
            f'{i*"- "}b{(size-1-i)*" -"} {i*"- "}X{(size-1-i)*" -"}' for i in range(size)]
        states2 = [
            f'{i*"- "}X{(size-1-i)*" -"} {i*"- "}b{(size-1-i)*" -"}' for i in range(size)]
        for base_state1, base_state2 in zip(states1, states2):
            for i in range(size-1):
                tmp_state1 = i*f'{empty} ' + \
                    base_state1 + (size-2-i)*f' {empty}'
                tmp_state2 = i*f'{empty} ' + \
                    base_state2 + (size-2-i)*f' {empty}'
                f.write(tmp_state1 + ' => ')
                f.write(tmp_state2 + '\n')
                f.write(tmp_state2 + ' => ')
                f.write(tmp_state1 + '\n')

        f.write('\n\n')

        f.write(f'GOAL b')
        for i in range(1, n+1):
            f.write(f' {i}')
