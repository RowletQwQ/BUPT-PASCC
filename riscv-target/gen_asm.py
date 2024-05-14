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

import os

def run_pascc(file, source_dir, dest_dir):
    filename = os.path.basename(file)
    try:
        with open(dest_dir + filename[:-4] + ".log", 'w') as log_file:
            subprocess.run(['../bin/pascc', '-i', file, '-o', dest_dir + filename[:-4] + ".s", '-D', '-d', '4'], stdout=log_file, stderr=subprocess.STDOUT, check=True, timeout=20)
    except (subprocess.CalledProcessError, subprocess.TimeoutExpired) as e:
        print(f"Error: {str(e)} for {filename}")
        file_path = dest_dir + filename[:-4] + ".s"
        if os.path.exists(file_path):
            os.remove(file_path)
        return False
    print(f"Assembly for {filename} generated successfully")
    return True

def gen_asm(source_dir, dest_dir):
    files = sorted([file for file in os.listdir(source_dir) if file.endswith('.pas')])
    with concurrent.futures.ThreadPoolExecutor() as executor:
        results = list(executor.map(run_pascc, files, [source_dir]*len(files), [dest_dir]*len(files)))
    successful_files = [file for file, success in zip(files, results) if success]
    failed_files = [file for file, success in zip(files, results) if not success]
    print(f"{Colors.GREEN} Successful files: {successful_files} {Colors.END}")
    print(f"{Colors.RED} Failed files: {failed_files} {Colors.END}")
            
os.chdir('../open_set')
gen_asm('.', '../riscv-target/asm/')