import os
import shutil

if "__main__" == __name__:
    root_dir = 'src'

    for subdir, dirs, files in os.walk(root_dir):
        # ignore the abstraction folder
        if 'abstractions' in subdir:
            continue
        for file in files:
            if file.endswith('.psvn'):
                file_path = os.path.join(subdir, file)
                parent_dir = os.path.basename(subdir)
                file_name = os.path.splitext(file)[0]
                if parent_dir != file_name:
                    new_dir = os.path.join(subdir, file_name)
                    os.makedirs(new_dir, exist_ok=True)
                    shutil.move(file_path, os.path.join(new_dir, file))

    PSVN_COMPILER_PATH = 'psvn/psvn2c'
    PSVNOPT = '--no_backwards_moves --history_len='
    PSVN_NAME = '--name='
    PSVN_HISTORY_LEN = [0, 1]
    BASE_FILE_PATH = 'src/utils/base.cpp'

    # copy core for psvn folder
    os.system('cp psvn/*.c .')

    # now we generate all the c files with the psvn2c compiler
    for subdir, dirs, files in os.walk(root_dir):
        # ignore the abstraction folder
        if 'abstractions' in subdir:
            continue
        for file in files:
            if file.endswith('.psvn'):
                file_path = os.path.join(subdir, file)
                for history_len in PSVN_HISTORY_LEN:
                    output_file_path = os.path.join(
                        subdir, file.replace('.psvn', f'_h{history_len}.c'))
                    print(
                        f'Generating {output_file_path} with history length {history_len}')
                    print(
                        f'{PSVN_COMPILER_PATH} {PSVNOPT}{history_len} {PSVN_NAME}{file.replace(".psvn", "")} < {file_path} > {output_file_path}')

                    os.system(
                        f'{PSVN_COMPILER_PATH} {PSVNOPT}{history_len} {PSVN_NAME}{file.replace(".psvn", "")} < {file_path} > {output_file_path}')
                    # copy the base file to the same directory and rename it to the output file name
                    shutil.copy(BASE_FILE_PATH, subdir)

                    # append to the beginning '#include "output_file_path"' to the base file
                    with open(os.path.join(subdir, 'base.cpp'), 'r+') as f:
                        content = f.read()
                        f.seek(0, 0)
                        f.write(
                            f'#include "{os.path.basename(output_file_path)}"\n' + content)

                    shutil.move(os.path.join(subdir, 'base.cpp'),
                                output_file_path.replace('.c', '.cpp'))

    # remove core c files
    os.system('rm *.c')
