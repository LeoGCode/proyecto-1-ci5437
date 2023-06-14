import pandas as pd
import os
from decimal import Decimal

result_dir = './results'
result_output_dir = './results/tex'
# filename = 'topspin_14_4_900.csv'


def replace_by_magnitude(x):
    if x < 100:
        return x
    else:
        magnitude = ''


if __name__ == "__main__":
    for filename in os.listdir(result_dir):
        if filename == '.gitkeep':
            continue
        if not filename.endswith('.csv'):
            continue
    # we read the data from the csv file
        data = pd.read_csv(f'./{result_dir}/{filename}',
                           index_col=[0, 1], header=[0, 1, 2])
        # we print the data
        # print(data)
        # we group the data by the first index and we calculate the mean
        cols = data.columns.tolist()
        # rearrange the columns to have f values first, then the g values, e and lastly the t values
        f_cols = [col for col in cols if 'f' in col]
        g_cols = [col for col in cols if 'g' in col]
        e_cols = [col for col in cols if 'e' in col]
        t_cols = [col for col in cols if 't' in col]
        cols = f_cols + g_cols + e_cols + t_cols
        data = data[cols]
        # we print the data
        data_grouped = data.groupby(level=0).mean().T.round(2)
        # we replace the values by their magnitude
        # data_grouped = data_grouped.applymap(replace_by_magnitude)
        # we save the data to csv
        data_grouped.to_csv(f'./{result_output_dir}/{filename[:-4]}.csv')
    # we print the data
    # print(data_grouped)
    # we separate the data by the first column
    # data_grouped_1 = data_grouped.iloc[:, 0:16].T.round(2)
    # data_grouped_2 = data_grouped.iloc[:, 16:33].T.round(2)
    # we print the data
    # print(data_grouped_1)
    # print(data_grouped_2)
    # we save the data to csv
    # data_grouped_1.to_csv(f'./{result_output_dir}/{filename[:-4]}_0.csv')
    # data_grouped_2.to_csv(f'./{result_output_dir}/{filename[:-4]}_1.csv')

    # # we calculate the mean of the data
    # mean_num_generated = data.applymap(lambda x: x[1]).mean()
    # # we print the mean
    # # print(mean_num_generated)
    # mean_num_expanded = data.applymap(lambda x: x[2]).mean()
    # # we print the mean
    # # print(mean_num_expanded)
    # # we create a new dataframe with only the elements 1 of the tuple
    # data_num_generated = data.applymap(lambda x: x[1])
    # # we print the data
    # print(data_num_generated.describe().round(2))
    # # we create a new dataframe with only the elements 2 of the tuple
    # data_num_expanded = data.applymap(lambda x: x[2])
    # # we print the data
    # print(data_num_expanded.describe().round(2))
    # # we create a new dataframe with only the elements 0 of the tuple
    # data_found = data.applymap(lambda x: x[0])
    # # we print the data
    # print(data_found.describe().round(2))
    # # we save each dataframe to csv
    # data_found.describe().round(2).to_csv(
    #     f'./{result_output_dir}/{filename[:-4]}_found.csv')
    # (data_num_generated.describe().round(2)).to_csv(
    #     f'./{result_output_dir}/{filename[:-4]}_num_generated.csv')
    # (data_num_expanded.describe().round(2)).to_csv(
    #     f'./{result_output_dir}/{filename[:-4]}_num_expanded.csv')
