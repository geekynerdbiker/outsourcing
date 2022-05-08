import data


def display_dict(a_dict, label=None, **kwargs):
    """
    Displays a dictionary formatted nicely.
    """
    if label:
        print(f"{label}:")
    for key, value in a_dict.items():
        print(f"{key:>25}: {value}")


def get_item_from_list(the_list):
    """
    Presents user with list of choices until they select an item from it.
    """
    valid_choices = range(1, len(the_list) + 1)
    while True:
        # Display choices and get input
        print("Select an item:")
        for item_label, item in enumerate(the_list, start=1):
            print(f"{item_label}: {item}")
        selected_label = input(">>>> ").strip()

        try:
            # Index is one less than user's choice integer

            if int(selected_label) not in valid_choices:
                # User's input isn't a valid choice
                print(f"Choice must be between 1 and {len(the_list)}")
                continue
            else:
                selected_index = int(selected_label.strip()) - 1
                # User's input is valid
                break
        except:
            # User's input can't be converted to an integer
            print("Invalid choice")
            continue
    # Return selected item from list
    return the_list[selected_index]


def get_column_type_dict(sample_row, column_type_dict, types=[str, int, float, bool], **kwargs):
    """
    Given a dictionary of CSV row data, return a dict of column names with
    user-selected data types.

    For each column, present user with sample data. Get selected data type for each
    until conversion is successful. Build dict of column names and data types.

    Returns dict with `column_type_dict` key and resulting dict as value.

    Assumes sample_row is representative of all data in CSV.
    """
    display_dict(column_type_dict, label="Current column data types:")

    data_type_dict = {}
    columns = sample_row.keys()

    for column in columns:
        while True:
            data = sample_row[column]
            print(f"What data type is {column}?\n  Sample data:\n  {data}\n")
            selected_type = get_item_from_list(types)
            try:
                selected_type(data)
                break
            except:
                # data could not be converted to that type
                print("Data could not be converted to that type. Make another selection.")
                types.remove(selected_type)

        data_type_dict[column] = selected_type
    return {
        "column_type_dict": data_type_dict
    }


def get_valid_row_index(row_list, default=1, prompt="Row to view"):
    """
    Gets a valid row_int got a given row_list
    """
    # Find highest row number
    maxrow_int = len(row_list)
    while True:
        print(f"Enter a row number from 1 to {maxrow_int}")
        row_choice_str = input(f"{prompt} (default: {default}):   ")

        if row_choice_str == "":
            # User just pressed enter; use default
            row_int = default
            break

        try:
            # User entered something; try to convert it to an integer
            row_int = int(row_choice_str)
        except:
            print("Please enter an integer")
            continue  # User must start over; repeat loop

        # Make sure integer is a valid row number
        if row_int < 1 or row_int > maxrow_int:
            print("Not a valid row number")
            continue  # User must start over; repeat loop
        else:
            break
    # The list index will be one less than the user-selected row number
    row_index = row_int - 1
    return row_index


def input_is_yes(message_str, default=None):
    """
    Displays `message` and collects validated yes/y/no/n input.
    Returns `True` for yes answers, `False` for no answers.

    Optional `default` parameter can be any yes or no value; if set,
    empty string acts as that answer. Also affects option
    formatting. 'y' or 'n' recommended.
    """

    yes_options_list = ["y", "yes", "ok", "yea", "yeah"]
    no_options_list = ["n", "no", "nope", "nah"]

    assert default in yes_options_list + no_options_list + [
        None], "`default` argument must be a form of yes, no, or None."

    if default in yes_options_list:
        options_str = f"({default.upper()}/n)"
        yes_options_list.append("")
    elif default in no_options_list:
        options_str = f"(y/{default.upper()})"
        no_options_list.append("")
    while True:
        choice_str = input(f'{message_str} {options_str}   ').strip().lower()

        if choice_str in yes_options_list:
            return True
        elif choice_str in no_options_list:
            return False
        else:
            print(f"{choice_str} is not valid input")
            continue


def present_choices(choices_dict):
    """
    Takes a dict with choice string keys and function dict
    values. Expects function dicts to have "description"
    and "function" keys/.

    Present choices to the user and return the
    corresponding function name.
    """
    while True:
        print("Main Menu:")

        choices_list = sorted(choices_dict.keys())
        for choice in choices_list:
            function_dict = choices_dict[choice]
            description = function_dict["description"]

            print(f"{choice}: {description}")

        choice_str = input("Make a selection:   ")

        if choice_str in choices_dict:
            function_dict = choices_dict[choice_str]
            function = function_dict["function"]
            return function
        elif choice_str == "exit":
            print("Goodbye")
            exit()
        else:
            print("Invalid selection")
            continue


def choose_csv():
    """
    Prints a list of CSVs visible to Python and returns the filename string
    the user selects from the list.

    User must enter an integer between one and the number of CSVs in the list
    of CSV returned by `data.get_csvs_list()`
    """
    new_filename_str = ""
    csvs_list = data.get_csv_filenames_list()
    while new_filename_str not in csvs_list:
        print("Available CSV files:")
        for i, filename in enumerate(csvs_list, start=1):
            print(f"{i} - {filename}")

        try:
            filenum = int(input(f"Enter a number between 1 and {i}:   "))
            new_filename_str = csvs_list[filenum - 1]
            print("Chosen CSV file:", new_filename_str, end="\n\n")
        except:
            # Can't understand user input. Ask again.
            print("Try again.")
            continue
    return new_filename_str

