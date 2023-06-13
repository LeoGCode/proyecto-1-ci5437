import pandas as pd
import os


def string_to_tuple(string):
    t = string.split(',')
    r = (True if 'True' in t[0] else False, int(t[1].strip().replace("'", '')
                                                ), int(t[2].strip().replace("'", '').replace(')', '')
                                                       ))
    return r


result_dir = './results'
result_output_dir = './results/tex'

if __name__ == "__main__":
    for filename in os.listdir(result_dir):
        if filename == '.gitkeep':
            continue
        if not filename.endswith('.csv'):
            continue
        # we read the data from the csv file
        data = pd.read_csv(f'./{result_dir}/{filename}',
                           index_col=[0, 1], header=[0, 1])
        # process the data to transform the string into a tuple
        data = data.applymap(string_to_tuple)
        # we print the data
        # print(data.describe())
        # we calculate the mean of the data
        mean_num_generated = data.applymap(lambda x: x[1]).mean()
        # we print the mean
        # print(mean_num_generated)
        mean_num_expanded = data.applymap(lambda x: x[2]).mean()
        # we print the mean
        # print(mean_num_expanded)
        # we create a new dataframe with only the elements 1 of the tuple
        data_num_generated = data.applymap(lambda x: x[1])
        # we print the data
        print(data_num_generated.describe().round(2))
        # we create a new dataframe with only the elements 2 of the tuple
        data_num_expanded = data.applymap(lambda x: x[2])
        # we print the data
        print(data_num_expanded.describe().round(2))
        # we create a new dataframe with only the elements 0 of the tuple
        data_found = data.applymap(lambda x: x[0])
        # we print the data
        print(data_found.describe().round(2))
        # we save each dataframe to csv
        data_found.describe().round(2).to_csv(
            f'./{result_output_dir}/{filename[:-4]}_found.csv')
        (data_num_generated.describe().round(2)).to_csv(
            f'./{result_output_dir}/{filename[:-4]}_num_generated.csv')
        (data_num_expanded.describe().round(2)).to_csv(
            f'./{result_output_dir}/{filename[:-4]}_num_expanded.csv')
