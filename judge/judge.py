import os
import subprocess

class Colors:
    YELLOW = '\033[33m'
    RED = '\033[31m'
    GRAY = '\033[90m'
    PURPLE = '\033[35m'
    END = '\033[0m'
    GREEN = '\033[32m'
    
def compile_and_run(directory):
    os.chdir(directory)
    ce_files = []
    wa_files = []
    tle_files = []
    re_files = []
    for file in os.listdir('.'):
        if file.endswith('.pas'):
            try:
                subprocess.run(['../bin/pascc', '-i', file], check=True)
                subprocess.run(['fpc', file], check=True)
                os.rename(file[:-4], file[:-4] + "_fpc")
                subprocess.run(['gcc', file[:-4] + ".c", '-o', file[:-4] + "_gcc"], check=True)
            except subprocess.CalledProcessError:
                ce_files.append(file)
                print(f"Error: Compilation failed for {file}")
                continue
            try:
                input_file = file[:-4] + ".in"
                if os.path.exists(input_file):
                    with open(input_file, 'r') as f:
                        input_data = f.read()
                    with open(file[:-4] + "_fpc.out", 'w') as f:
                        subprocess.run(['./'+file[:-4] + "_fpc"], input=input_data, text=True, stdout=f, check=True)
                    with open(file[:-4] + "_gcc.out", 'w') as f:
                        subprocess.run(['./'+file[:-4] + "_gcc"], input=input_data, text=True, stdout=f, check=True, timeout=5)
                    with open(file[:-4] + "_fpc.out", 'r') as f1, open(file[:-4] + "_gcc.out", 'r') as f2:
                        if f1.read() != f2.read():
                            print(f"Error: Output mismatch for {file}")
                else:
                    with open(file[:-4] + "_fpc.out", 'w') as f:
                        subprocess.run(['./'+file[:-4] + "_fpc"], text=True, stdout=f, check=True)
                    with open(file[:-4] + "_gcc.out", 'w') as f:
                        subprocess.run(['./'+file[:-4] + "_gcc"], text=True, stdout=f, check=True, timeout=5)
                    with open(file[:-4] + "_fpc.out", 'r') as f1, open(file[:-4] + "_gcc.out", 'r') as f2:
                        if f1.read() != f2.read():
                            print(f"Error: Output mismatch for {file}")
                            wa_files.append(file)
            except subprocess.CalledProcessError:
                re_files.append(file)
                print(f"Error: Command failed for {file}")
                
            except subprocess.TimeoutExpired:
                print(f"Error: Command timed out for {file}")
                tle_files.append(file)
    return ce_files, wa_files, tle_files, re_files


os.chdir('../open_set')
open_ce, open_wa, open_tle, open_re = compile_and_run('.')
os.chdir('../hidden_set')
hidden_ce, hidden_wa, hidden_tle, hidden_re = compile_and_run('.')
os.chdir('..')
for file in os.listdir('open_set'):
    if file.endswith('.c') or file.endswith('.out') or file.endswith('_fpc') or file.endswith('_gcc') or file.endswith('.o'):
        os.remove(f'open_set/{file}')
for file in os.listdir('hidden_set'):
    if file.endswith('.c') or file.endswith('.out') or file.endswith('_fpc') or file.endswith('_gcc') or file.endswith('.o'):
        os.remove(f'hidden_set/{file}')

print("Open set:")
if len(open_ce) == 0 and len(open_wa) == 0 and len(open_tle) == 0 and len(open_re) == 0:
    print(f"{Colors.GREEN}All tests passed{Colors.END}")
else:
    print("Some tests failed")
    print(f"{Colors.YELLOW}Compilation errors: {open_ce}{Colors.END}")
    print(f"{Colors.RED}Wrong answer: {open_wa}{Colors.END}")
    print(f"{Colors.GRAY}Time limit exceeded: {open_tle}{Colors.END}")
    print(f"{Colors.PURPLE}Runtime errors: {open_re}{Colors.END}")
print("Hidden set:")
if len(hidden_ce) == 0 and len(hidden_wa) == 0 and len(hidden_tle) == 0 and len(hidden_re) == 0:
    print("{Colors.GREEN}All tests passed{Colors.END}")
else:
    print("Some tests failed")
    print(f"{Colors.YELLOW}Compilation errors: {hidden_ce}{Colors.END}")
    print(f"{Colors.RED}Wrong answer: {hidden_wa}{Colors.END}")
    print(f"{Colors.GRAY}Time limit exceeded: {hidden_tle}{Colors.END}")
    print(f"{Colors.PURPLE}Runtime errors: {hidden_re}{Colors.END}")