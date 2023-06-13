import os
import shutil
import re

root_dir = 'src'
bin_dir = 'bin'

if "__main__" == __name__:
    cmake_base = 'CMakeLists.txt.base'
    cmake_file = 'CMakeLists.txt'
    psvn_base_path = 'src/utils/psvn.base'
    psvn_file_path = 'src/utils/psvn.hpp'
    # copy the base file to the same directory and rename it to the output file name
    # replace the placeholder with the actual file names
    # the placeholder are 'name', 'problem.c' and 'problem.cpp'

    for subdir, dirs, files in os.walk(root_dir):
        # ignore the abstraction folder
        if 'abstractions' in subdir:
            continue
        for f in files:
            if f.endswith('.psvn'):
                problem_name = os.path.splitext(f)[0]
                for i in range(2):
                    file_name = f'{problem_name}_h{i}'
                    problem_path = os.path.join(subdir, file_name)
                    shutil.copy(cmake_base, cmake_file)
                    with open(cmake_base, 'r') as f:
                        with open(cmake_file, 'w') as f1:
                            content = f.read()
                            new_content = content.replace('name', file_name)
                            new_content = new_content.replace(
                                'problem.c', f'{problem_path}.c')
                            new_content = new_content.replace(
                                'problem.cpp', f'{problem_path}.cpp')
                            f1.write(new_content)
                            f1.close()

                    with open(f'{problem_path}.c', 'r') as f:
                        # find for '#define NUMVARS \d+'
                        # replace the number with the number of variables
                        content = f.read()
                        num_vars = re.findall(
                            r'#define NUMVARS \d+', content)[0]
                        num_vars = num_vars.split(' ')[-1]

                        with open(psvn_base_path, 'r') as f1:
                            with open(psvn_file_path, 'w') as f2:
                                content = f1.read()
                                new_content = content.replace(
                                    'num_states_vars', num_vars)
                                f2.write(new_content)
                                f2.close()

                    for subdir2, dirs2, files2 in os.walk(bin_dir):
                        if not problem_name in dirs2:
                            os.makedirs(os.path.join(bin_dir, problem_name))
                        break

                    os.system(
                        f'cd build && cmake .. && make && mv {file_name} ../bin/{problem_name}')
