# this script is used to create a sqlite db from csv 
import csv
import requests
import time
import os
from tqdm import tqdm
import sqlite3
import zipfile

current_working_dir = dir_path = os.path.dirname(os.path.realpath(__file__))
csv_filename = current_working_dir + '\olam-enml.csv\olam-enml.csv'
url = 'https://olam.in/open/enml/olam-enml.csv.zip'
zip_filename = current_working_dir + '\olam-enml.csv.zip'
extract_dir = current_working_dir+'\olam-enml.csv'

def download_zip_file(url, zip_filename):
    print("Download started.")
    response = requests.get(url, stream=True)
    total_size = int(response.headers.get('content-length', 0))
    with open(zip_filename, 'wb') as f:
        progress_bar = tqdm(total=total_size, unit='B', unit_scale=True)
        for chunk in response.iter_content(1024):
            if chunk:
                f.write(chunk)
                progress_bar.update(len(chunk))
        progress_bar.close()
    while True:
        current_size = os.path.getsize(zip_filename)
        if current_size == total_size:
            break
        time.sleep(1)
    print('Download completed!')

def extract_zip_file(zip_filename, extract_dir):
    print("Extraction started")
    with zipfile.ZipFile(zip_filename, 'r') as zip_file:
        file_list = zip_file.namelist()
        progress_bar = tqdm(total=len(file_list), unit='file')

        for file in file_list:
            zip_file.extract(file, extract_dir)
            progress_bar.update(1)
        progress_bar.close()
    print('Extraction completed!')

def init_sqlite_db():
    db_location = current_working_dir+'\olamdict.db'
    if os.path.exists(db_location):
        os.remove(db_location)
        print("Exisiting db deleted")
    try:
        connection = sqlite3.connect(db_location)
        curser = connection.cursor()
        curser.execute('''CREATE TABLE IF NOT EXISTS data
             (id TEXT, english_word TEXT, part_of_speech TEXT, malayalam_definition TEXT)''')
        connection.commit()
        return connection
    except Exception as e:
        print(e)

def transfer_data_to_db(connection, csv_filename):
    total_count = 0
    sucess_count = 0 
    error_count = 0
    with open(csv_filename, 'r') as file:
        reader = csv.reader(file, delimiter='\t')
        for row in reader:
            total_count +=1
            try:
                connection.execute("INSERT INTO data (id, english_word, part_of_speech, malayalam_definition) VALUES (?, ?, ?, ?)", row)
                connection.commit()
                sucess_count +=1
                print("{}/{}, <->  {} -> added to db".format(sucess_count, total_count, row[1]))
            except Exception as e:
                print(e)
                error_count +=1

    print("Total sucessful attempt : {} , Error occured : {}".format(sucess_count, error_count))
    connection.close()

if __name__ == "__main__":
    zip_exists = False
    csv_exists = False
    if os.path.exists(zip_filename):
        print("Zip file already downloaded ")
        zip_exists = True
    if os.path.exists(csv_filename):
        print("csv file is exists in the extracted folder ")
        csv_exists = True
    if (not csv_exists):
        if(zip_exists):
            extract_zip_file(zip_filename,extract_dir)
            csv_exists = True
        else:
            download_zip_file(url, zip_filename)
            extract_zip_file(zip_filename,extract_dir)
            csv_exists = True
            zip_exists = True
    else:
        zip_exists = True

    if(zip_exists and csv_exists):
        connection = init_sqlite_db()
        transfer_data_to_db(connection, csv_filename)