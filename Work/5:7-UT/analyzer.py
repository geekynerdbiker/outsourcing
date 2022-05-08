from pprint import pprint
import interface


def new_function(row_dict_list, column_type_dict, columns, number_of_rows, **kwargs):
    """
    Given a list of row dictionaries, column names, and number of rows,
    prints counts and percentages of categorical variable of columns
    selected by the user.
    """

    columns_to_analyze = []
    for column in columns:
        if interface.input_is_yes(f"Analyze {column}?", default='n'):
            columns_to_analyze.append(column)

    if columns_to_analyze == []:
        print("No columns selected")
        return

    for selected_column in columns_to_analyze:
        print(f"{selected_column}:")
        count_dict = {}
        width = 25
        for row_dict in row_dict_list:
            value = row_dict[selected_column]
            width = max(width, len(str(value)))
            if value in count_dict:
                count_dict[value] += 1
            else:
                count_dict[value] = 1

        # print(number_of_rows)
        # pprint(count_dict)
        for category, count in count_dict.items():
            print(f"{category:>{width}} {count:>5} {count / number_of_rows:>5.1%}")
        print()
    input("Press enter to return to main menu. ")


def get_numerical_columns_list(column_type_dict, **kwargs):
    """
    Returns list of column names having numerical data types.

    Will return empty list if no columns are numerical.
    """
    numerical_columns = []
    numerical_types = [int, float]
    for column, data_type in column_type_dict.items():
        if data_type in numerical_types:
            numerical_columns.append(column)
    return numerical_columns


def your_new_function(row_dict_list, **kwargs):
    """
    TODO: Implement your new function.

    Change this docstring and the code inside it.
    """
    print("This is new functionality")
    parameters = locals()
    print("Parameters available here:")
    pprint(parameters)
