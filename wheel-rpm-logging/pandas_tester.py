import os
import pandas as pd
import openpyxl

"""
Important steps

install latest version of python 
pip install pandas
pip install serial
pip install xlwt
pip install openpyxl
"""

def main():
    df = pd.DataFrame([[11, 21, 31], [12, 22, 32], [31, 32, 33]], columns=['a', 'b', 'c'])
    df.to_excel('test.xlsx', sheet_name='new_sheet_name')


if __name__ == "__main__":
    main()
