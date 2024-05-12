import os
import subprocess
import shutil

class Colors:
    YELLOW = '\033[33m'
    RED = '\033[31m'
    GRAY = '\033[90m'
    PURPLE = '\033[35m'
    END = '\033[0m'
    GREEN = '\033[32m'
    
import concurrent.futures

def run_pascc(file, source_dir, dest_dir):
    filename = os.path.basename(file)
    try:
        with open(dest_dir + filename[:-4] + ".log", 'w') as log_file:
            subprocess.run(['../bin/pascc', '-i', file, '-o', dest_dir + filename[:-4] + ".s", '-D', '-d', '3'], stdout=log_file, check=True)
    except subprocess.CalledProcessError:
        print(f"Error: Compilation failed for {filename}")
        return
    print(f"Assembly for {filename} generated successfully")

def gen_asm(source_dir, dest_dir):
    files = [file for file in os.listdir(source_dir) if file.endswith('.pas')]
    with concurrent.futures.ThreadPoolExecutor() as executor:
        executor.map(run_pascc, files, [source_dir]*len(files), [dest_dir]*len(files))
            
os.chdir('../open_set')
gen_asm('.', '../riscv-target/asm/')