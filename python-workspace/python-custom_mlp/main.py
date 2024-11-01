import time

from datamodule import NLDataset
from models.naive_bayes import NaiveBayes
from models.decision_tree import DecisionTree
from models.mlp import MLP
from custom_models.custom_mlp import CustomMLP
from utils import set_seed, save_test_result


class Dotdict(dict):
    __getattr__ = dict.get
    __setattr__ = dict.__setitem__
    __delattr__ = dict.__delitem__


def run_model(config, dataset, model_type):
    config = Dotdict(config) if config else None

    if model_type == 'naive_bayes':
        model = NaiveBayes(dataset)
    elif model_type == 'decision_tree':
        model = DecisionTree(dataset)
    elif model_type == 'mlp':
        model = MLP(config, dataset)
    elif model_type == 'custom_mlp':
        model = CustomMLP(config, dataset)

    running_start = time.time()
    result = model.run()
    print("Model Execution time : {:.4f} sec".format(
        time.time() - running_start))
    print()

    return result


def main():
    set_seed(42)

    ############################ Please write your own name and student ID #############################
    NAME = ""
    ID = ""
    ####################################################################################################

    dataset = NLDataset()
    result = dict()

    ############################################## EDIT ################################################
    mlp_config = {
        'input_size': dataset.number_of_features,
        'hidden_size': 200,
        'output_size': dataset.number_of_labels,
        'epochs': 30,
    }

    run_custom = True  # Set True if implement a model
    custom_mlp_config = {
        'input_size': dataset.number_of_features,
        'hidden_size': 350,
        'output_size': dataset.number_of_labels,
        'learning_rate': 0.0075,
        'epochs': 30,
    }
    ####################################################################################################

    nb_result = run_model(None, dataset, model_type='naive_bayes')
    result['naive_bayes'] = nb_result

    dt_result = run_model(None, dataset, model_type='decision_tree')
    result['decision_tree'] = dt_result

    mlp_result = run_model(mlp_config, dataset, model_type='mlp')
    result['mlp'] = mlp_result

    if run_custom:
        custom_mlp_result = run_model(
            custom_mlp_config, dataset, model_type='custom_mlp')
        result['custom_mlp'] = custom_mlp_result
    else:
        result['custom_mlp'] = None

    save_test_result(result, std_name=NAME, std_id=ID)


if __name__ == '__main__':
    main()
