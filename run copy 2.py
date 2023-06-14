import re
import os
import sys
import subprocess
import pandas as pd

root_dir = 'src'
bin_dir = 'bin'
benchmark_dir = 'benchmarks'
results_dir = 'results'

if "__main__" == __name__:

    if len(sys.argv) >= 2:
        threshold = sys.argv[1]
    else:
        threshold = 30
        print('No threshold provided, using default value 30, to change it run:')
        print('python run.py <threshold>')

    print(f'Using threshold {threshold}')

    search_algo = ['astar', 'idastar']
    dataframes = []

    # now we execute each of the binaries with the corresponding benchmark
    for benchmark, bin_name in zip(os.listdir(benchmark_dir), os.listdir(bin_dir)):
        bin_files = os.listdir(f'./{bin_dir}/{bin_name}')
        benchmark_files = os.listdir(f'./{benchmark_dir}/{benchmark}')
        index = [[], []]
        columns = [[], []]
        bin_dt = pd.DataFrame()
        if 'puzzle' not in bin_name:
            continue
        for bin_file in bin_files:
            if 'h2' in bin_file:
                continue
            file_dt = pd.DataFrame()
            for benchmark_file in benchmark_files:
                with open(f'./{benchmark_dir}/{benchmark}/{benchmark_file}', 'r') as f:
                    lines_no_repeats = set(f.readlines())
                    for line in lines_no_repeats:
                        if line == '\n':
                            continue
                        algo_dt = pd.DataFrame()
                        for algo in search_algo:
                            # we capture command output
                            l = line.replace('\n', '')
                            print(
                                f'./{bin_dir}/{bin_name}/{bin_file} {algo} {l} {threshold} {bin_name} manhattan')

                            output = subprocess.check_output(
                                [f'./{bin_dir}/{bin_name}/{bin_file}', algo, l, threshold, bin_name, 'manhattan'])
                            # we split the output by new line
                            output = output.decode('utf-8')
                            print(output)
                            if re.search(r'Solution found!', output):
                                found = True
                            else:
                                found = False
                            num_states = re.findall(r'\d+', output)
                            num_generated = num_states[0]
                            num_expanded = num_states[1]
                            # we store the output in a dataframe
                            algo_dt[
                                f'{bin_file}_{algo}'
                            ] = [(found, num_generated, num_expanded)]
                            # print the dataframes
                            # print(algo_dt)

                            isbef = [i for i, x in enumerate(
                                index[0]) if x == benchmark_file]
                            isel = [i for i, x in enumerate(
                                index[1]) if x == line.replace('\n', '')]
                            add_index = True
                            for i in isbef:
                                if i in isel:
                                    add_index = False
                            if add_index:
                                index[0].append(benchmark_file)
                                index[1].append(line.replace('\n', ''))
                            isbif = [i for i, x in enumerate(
                                columns[0]) if x == bin_file]
                            isa = [i for i, x in enumerate(
                                columns[1]) if x == algo]
                            add_column = True
                            for i in isbif:
                                if i in isa:
                                    add_column = False
                            if add_column:
                                # if not (bin_file in columns[0] and algo in columns[1]):
                                columns[0].append(bin_file)
                                columns[1].append(algo)
                        file_dt = pd.concat(
                            [file_dt, algo_dt], ignore_index=True)
                        # print(file_dt)

            bin_dt = pd.concat([bin_dt, file_dt], axis=1)
            # print(bin_dt)
            # file_dt.to_csv(f'./{results_dir}/{bin_name}_{bin_file}.csv')

        print(index)
        print(columns)
        bin_dt.index = pd.MultiIndex.from_tuples(
            list(zip(*index)), names=['file', 'instance'])
        bin_dt.columns = pd.MultiIndex.from_tuples(
            list(zip(*columns)), names=['pruning', 'algorithm'])
        dataframes.append(bin_dt)
        bin_dt.to_csv(f'./{results_dir}/{bin_name}_t{threshold}_manhattan.csv')
        # print(bin_dt)

    # we save the dataframes to csv files
    # for df, benchmark in zip(dataframes, os.listdir(benchmark_dir)):
    #     df.to_csv(f'./{results_dir}/{benchmark}.csv')
