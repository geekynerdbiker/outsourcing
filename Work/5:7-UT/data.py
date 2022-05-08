import glob
import csv
from random import choice
import interface
import explorer


def get_new_csv_data_dict(new_data_file=None, ask_user=True, extra_info=True, **kwargs):
    """
    Return a new `csv_data_dict` based on a default dict.

    The `new_csv_dict` function variable should contain keys and default values
    expected by any functions called by the main menu interface. Add new entries
    to it when expanded program functionality will expect all CSV dictionaries to
    contain them by default.

    Optional argument extra_info controls whether summary information is printed.
    Optional keyword argument ask_user is passed to `get_selected_columns_list`.
    """
    if new_data_file == None:
        filename = interface.choose_csv()
    else:
        filename = new_data_file

    # Dictionary with all keys expected by default functions
    row_dict_list = get_row_dict_list(filename, **kwargs)
    kwargs["row_dict_list"] = row_dict_list
    sample_row = choice(row_dict_list)
    columns = sample_row.keys()
    new_csv_dict = {
        "filename": filename,
        "row_dict_list": row_dict_list,
        "sample_row": sample_row,
        "number_of_rows": len(row_dict_list),
        "number_of_columns": len(columns),
        "columns": columns,
        "selected_columns": get_selected_columns_list(ask_user=ask_user, **kwargs),
        "column_type_dict": dict(zip(columns, [str for x in columns]))
    }
    if extra_info:
        explorer.print_csv_info_from_dict(new_csv_dict)
    return new_csv_dict


def get_row_dict_list(filename_str='ischools-clean.csv', **kwargs):
    """
    Returns a list of dictionaries from a CSV file.

    Row dictionaries take keys from the CSV column header. Values are the data in that column of the row.

    Optional `filename_str` parameter changes the file read in.
    """
    with open(filename_str, newline='') as file:
        reader = csv.DictReader(file)
        row_dict_list = list(reader)

    return row_dict_list


def get_csv_filenames_list():
    """
    Returns a list of .csv files visible to the program.
    """
    return glob.glob(r"*.csv")


def get_selected_columns_list(row_dict_list, ask_user=True, **kwargs):
    """
    Get a list of columns to include when printing CSV data.

    Columns are keys of the first dictionary in row_list
    If `ask_user` is `True`, prompt the user for each column heading.
    Otherwise, inlcude all columns.

    Returns a list of column name strings.
    """

    first_row = row_dict_list[0]
    columns = list(first_row.keys())

    print(f"There are {len(columns)} columns.")
    if ask_user and interface.input_is_yes(f"Select which to print?", default='y'):
        selected_columns = []
        for column in columns:
            selected = interface.input_is_yes(f"   Do you want {column} in simplified print view?", default='n')
            if selected:
                selected_columns.append(column)
    else:
        print(f"All columns will be printed.")
        selected_columns = columns
    return selected_columns


def get_selected_columns_list_in_dict(**kwargs):
    """
    Calls `get_selected_columns_list` and returns result as dictionary compatible
    with main menu architecture.
    """
    return {
        "selected_columns": get_selected_columns_list(**kwargs)
    }


