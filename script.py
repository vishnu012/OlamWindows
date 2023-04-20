# this script is used to create a sqlite db from csv 
import csv
import os
import sqlite3

current_working_dir = dir_path = os.path.dirname(os.path.realpath(__file__))
csv_file_loc = current_working_dir + '\olam-enml.csv\olam-enml.csv'

def init_sqlite_db():
    db_location = current_working_dir+'\\resources\dict.db'
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

if __name__ == "__main__":
    total_count = 0
    sucess_count = 0 
    error_count = 0
    connection = init_sqlite_db()
    with open(csv_file_loc, 'r') as file:
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