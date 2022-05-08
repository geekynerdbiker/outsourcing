import analyzer, explorer, data, interface
from pprint import pprint


def get_interface_choices_dict():
    """
    Returns a dict that has interface choice keys and values containing
    an inner dict specifying the function the choice should call and
    a description to display to the user.

    Changing the returned dict is the main API to alter the program's
    main menu behavior. Pass dict to `interface.present_choices()` to
    display main menu and call the returned function in response to user
    input.
    """
    # Since this dict contains function names, wrapping it in a
    # function avoids circular imports.

    # Note that this dict is returned without first assigning it a name.
    return {
        "1": {
            "function": explorer.browse_rows,
            "description": "Browse rows of data"
        },
        "2": {
            "function": explorer.print_random_row,
            "description": "Print random row"
        },
        "3": {
            "function": explorer.print_specific_row,
            "description": "Print specific row"
        },
        "4": {
            "function": data.get_new_csv_data_dict,
            "description": "Change data file"
        },
        "5": {
            "function": data.get_selected_columns_list_in_dict,
            "description": "Select columns to print"
        },
        "6": {
            "function": interface.get_column_type_dict,
            "description": "Select column data types"
        },
        "7": {
            "function": analyzer.new_function,
            "description": "Get counts and percentages of categorical values"
        }

    }


def main(filename_str='ischools-clean.csv'):
    """
    Main entrypoint of program. Loads data from file specified by
    `filename_str` as dict returned from `data.get_new_csv_data_dict`.

    Main loop of program repeatedly presents user with main menu choices
    returned by `get_interface_choices_dict`, calls the function corresponding
    to user's input with `csv_data_dict` as argument, and updates that dict if
    the function returns a dict.

    All functions named in `interface_choices_dict` should accept keyword arguments
    (i.e. include a `**kwargs` parameter) and return either `None` or a dictionary
    with some subset of the keys in `csv_data_dict`.
    """
    print("Welcome to the CSV Explorer and Analyzer\n")

    interface_choices_dict = get_interface_choices_dict()

    csv_data_dict = data.get_new_csv_data_dict(new_data_file=filename_str, extra_info=True, ask_user=False)
    # pprint(csv_data_dict)

    while True:
        user_func = interface.present_choices(interface_choices_dict)
        returned_val = user_func(**csv_data_dict)
        if returned_val == None:
            continue
        else:
            # The function returned a value; update arguments dict passed to future functions
            assert isinstance(returned_val, dict), "Any returned value should be a dict"
            csv_data_dict.update(returned_val)


if __name__ == "__main__":
    # Call the `main` function only if this file is the one being executed.
    # Allows other files to import from it without circular imports.
    main()

