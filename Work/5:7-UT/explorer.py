import data
import interface
import random


def print_row(row, selected_columns, **kwargs):
    """
    Takes a row dict of header keys and data values pairs and prints it, one pair per line.
    """
    # Print right-justified key, then value
    for key in selected_columns:
        print(f"{key:>25}:  {row[key]}")


def browse_rows(row_dict_list, **kwargs):
    """
    Allows the user to browse rows of data.

    Start from 1 if `config_dict["start-from-one"]` is `True`.
    Otherwise, get a valid row integer from user and start there.

    Returns if user declines to continue or once last row is printed.
    """
    # Get desired first row from user
    first_row_int = interface.get_valid_row_index(row_dict_list, prompt="Start row")

    for i, line in enumerate(row_dict_list[first_row_int:], start=first_row_int):
        print(f"Row {i}:")
        print_row(line, **kwargs)

        if interface.input_is_yes("Contine?", default='y'):
            continue
        else:
            return


def print_specific_row(row_dict_list, **kwargs):
    """
    Prints a specific row of data specified by the user.

    Uses `interface.get_valid_row_int` to ensure user selects valid row number.

    Returns when user declines to print another row.
    """
    # Print rows one by one til user exits
    while True:
        row_int = interface.get_valid_row_index(row_dict_list)

        print_row(row_dict_list[row_int], **kwargs)

        if interface.input_is_yes("Print another specific row?", default='n'):
            # If the user wants to print another row, repeat the loop
            continue
        else:
            # Otherwise, return to main menu
            return


def print_random_row(row_dict_list, **kwargs):
    """
    Prints a random row of data.

    Returns when user declines to print another row.
    """
    while True:
        # Pick a random list index (insted of using random.choice),
        # so that we can print the row number for the user.
        random_row_index = random.randrange(len(row_dict_list))
        # The row number is the list index + 1
        random_row_number = random_row_index + 1
        # Get the random row
        random_row_dict = row_dict_list[random_row_index]

        print(f"Row {random_row_number}:")
        print_row(random_row_dict, **kwargs)

        if interface.input_is_yes("Print another random row?", default='y'):
            # If the user wants to print another row, repeat the loop
            continue
        else:
            # Otherwise, return to main menu
            return


def print_csv_info_from_dict(csv_dict, **kwargs):
    """
    Takes a `csv_dict` and displays info about a CSV file to user.
    """
    print("Current file:", csv_dict["filename"])
    print(f"Data contains {csv_dict['number_of_columns']} columns and {csv_dict['number_of_rows']} rows.\n")

    print("\nSample Row:")
    print_row(csv_dict["sample_row"], csv_dict["selected_columns"])
    print("\n")

