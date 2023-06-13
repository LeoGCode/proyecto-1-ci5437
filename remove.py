import os

csv_dir = './report/tex'

if __name__ == "__main__":
    for dirname in os.listdir(csv_dir):
        if dirname == '.gitkeep':
            continue
        if not dirname.endswith('.csv'):
            continue
        with open(f'{csv_dir}/{dirname}', 'r+') as f:
            content = f.read()
            content = content.replace('_', '')
            content = content.replace('%', '')
            f.seek(0)
            f.write(content)
            f.truncate()
