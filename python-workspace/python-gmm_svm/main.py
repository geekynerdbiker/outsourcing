import os
import numpy as np
import librosa
from sklearn.svm import SVC
from sklearn.mixture import GaussianMixture
from sklearn.metrics import accuracy_score


def convert_to_mfccs(file_path):
    y, sr = librosa.load(file_path)
    total_length = len(y)
    quarter_length = total_length // 4

    mfccs = []
    for i in range(4):
        start = i * quarter_length
        end = (i + 1) * quarter_length
        mfcc = librosa.feature.mfcc(y=y[start:end], sr=sr, n_mfcc=13)
        mfccs.append(np.mean(mfcc, axis=1))
    return mfccs


def run(model='SVM'):
    speaker_files = [os.path.join('data', f'{str(i + 1).zfill(3)}.wav') for i in range(10)]
    accuracies = []

    for i in range(4):
        train_mfccs = []
        train_labels = []
        test_mfccs = []
        test_labels = []

        for label, file in enumerate(speaker_files):
            mfccs = convert_to_mfccs(file)

            test_mfcc = mfccs[i]
            train_mfcc = [mfcc for j, mfcc in enumerate(mfccs) if j != i]

            train_mfccs.extend(train_mfcc)
            train_labels.extend([label] * len(train_mfcc))

            test_mfccs.append(test_mfcc)
            test_labels.append(label)

        train_mfccs = np.array(train_mfccs)
        train_labels = np.array(train_labels)
        test_mfccs = np.array(test_mfccs)
        test_labels = np.array(test_labels)

        if model == 'SVM':
            if len(np.unique(train_labels)) > 1:
                svm = SVC(probability=True).fit(train_mfccs, train_labels)

                predictions = []
                for mfcc in test_mfccs:
                    predicted_label = svm.predict([mfcc])[0]
                    predictions.append(predicted_label)

                accuracy = accuracy_score(test_labels, predictions)
                accuracies.append(accuracy)

                print(f"Fold {i + 1}: Accuracy = {accuracy}")
        else:
            gmms = []
            for label in range(10):
                label_train_mfccs = train_mfccs[train_labels == label]
                if len(label_train_mfccs) > 0:
                    gmm = GaussianMixture(n_components=1, covariance_type='diag').fit(label_train_mfccs)
                    gmms.append(gmm)
                else:
                    gmms.append(None)

            predictions = []
            for mfcc in test_mfccs:
                log_likelihoods = [gmm.score([mfcc]) if gmm is not None else -np.inf for gmm in gmms]
                predicted_label = np.argmax(log_likelihoods)
                predictions.append(predicted_label)

            accuracy = accuracy_score(test_labels, predictions)
            accuracies.append(accuracy)

            print(f"Fold {i + 1}: Accuracy = {accuracy}")

    final_accuracy = np.max(accuracies)
    print(f"Final Accuracy: {final_accuracy}")


print("[ GMM ]")
run(model='GMM')

print("[ SVM ]")
run(model='SVM')
