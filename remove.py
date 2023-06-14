import os
import re
import shelve
from decimal import Decimal

csv_dir = './results/tex'


def replace_by_magnitude(x):
    result = Decimal(x).normalize()

    if result < 9999:
        return result.to_eng_string()
    else:
        return 'E' + str(result.adjusted())


if __name__ == "__main__":
    for dirname in os.listdir(csv_dir):
        if dirname == '.gitkeep':
            continue
        if not dirname.endswith('.csv'):
            continue
        with open(f'{csv_dir}/{dirname}', 'r+') as f:
            content = f.read()
            print(dirname[:-8])
            element = content.split(',')
            new_content = ''
            for i, e in enumerate(element):
                digs = re.findall(r'\d+\.?\d+', e)
                fe = e
                for dig in digs:
                    fe = fe.replace(dig, replace_by_magnitude(dig))
                new_content += fe

                if i < len(element) - 1:
                    new_content += ','
            content = new_content

            # content = content.replace('pruning,', '')
            # regex = re.escape(dirname[:-10]) + r'_h\d,'
            # content = re.sub(regex, '', content)
            content = content.replace(dirname[:-8], '')
            content = content.replace('_', '')
            content = content.replace('%', '')
            f.seek(0)
            f.write(content)
            f.truncate()
        # move the vile to
