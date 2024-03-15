import os
import subprocess
import argparse
import sys

parser = argparse.ArgumentParser(description='Test script.')
parser.add_argument('--test_dir', type=str, default='../hidden_set',
                    help='The directory of test files.')
args = parser.parse_args()

test_dir = args.test_dir
exit_status = 0

for file in os.listdir(test_dir):
    if os.path.isfile(os.path.join(test_dir, file)) and file.endswith('.pas'):
        print(f'Testing {file}')
        output = ''
        try:
            output = subprocess.check_output(['../bin/IR_TEST', '-i', os.path.join(test_dir, file),'-d','4'], stderr=subprocess.STDOUT)
            print(output.decode('utf-8'))
            sys.stdout.flush()
            print(f'Testing {file} done')
        except subprocess.CalledProcessError as e:
            print(e.output.decode('utf-8'))
            sys.stdout.flush()
            print(f'Testing {file} failed')
            exit_status = e.returncode

exit(exit_status)