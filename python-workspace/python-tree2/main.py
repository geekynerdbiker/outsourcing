import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from statsmodels.formula.api import ols
import seaborn as sns
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.linear_model import LinearRegression, LogisticRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score, confusion_matrix, accuracy_score, \
    precision_score, recall_score, f1_score, roc_auc_score
from sklearn import tree
from math import log2


# PROB 1
def prob1():
    hospital = pd.read_csv("hospital.txt", sep="\t")
    print(hospital.describe())

    # 1-1
    sns.pairplot(data=hospital)
    plt.show()

    # 1-2
    print("correlation analysis")
    print(hospital.corr())

    # 1-3
    # 1)
    print(hospital.isnull().sum())

    # 3)
    train, test = train_test_split(hospital, test_size=0.2, random_state=2)

    target = ['InfctRsk']
    features = ['ID', 'Stay', 'Age', 'Culture', 'Xray', 'Beds', 'MedSchool', 'Region', 'Census', 'Nurses', 'Facilities']

    X_train = train[features]
    X_test = test[features]
    y_train = train[target]
    y_test = test[target]

    model = ols("InfctRsk ~ ID+Stay+Age+Culture+Xray+Beds+MedSchool+Region+Census+Nurses+Facilities", hospital).fit()

    # 4)
    print(model.summary())

    # 5)
    y_pred = model.predict(X_test)
    print('mae:', mean_absolute_error(y_test, y_pred))
    print('mse:', mean_squared_error(y_test, y_pred))
    print('rmse:', mean_squared_error(y_test, y_pred) ** 0.5)
    print('r2:', r2_score(y_test, y_pred))

    # 6)
    _, ax = plt.subplots()
    sns.scatterplot(x=model.fittedvalues, y=model.resid_pearson)
    ax.axhline(y=0)
    plt.xlabel("fitted values")
    plt.ylabel("residuals")
    plt.show()

    # 1-4
    # 1)
    model = ols("InfctRsk ~ Stay+Culture+Xray+MedSchool+Region+Facilities", hospital).fit()
    print(model.summary())

    # 2)
    y_pred = model.predict(X_test)
    print('mae:', mean_absolute_error(y_test, y_pred))
    print('mse:', mean_squared_error(y_test, y_pred))
    print('rmse:', mean_squared_error(y_test, y_pred) ** 0.5)
    print('r2:', r2_score(y_test, y_pred))

    # 3)
    _, ax = plt.subplots()
    sns.scatterplot(x=model.fittedvalues, y=model.resid_pearson)
    ax.axhline(y=0)
    plt.xlabel("fitted values")
    plt.ylabel("residuals")
    plt.show()


# PROB 2
def prob2():
    handspan = pd.read_csv("handspan.txt", sep="\t")
    # 1)
    print(handspan.isnull().sum())

    # 3)
    train, test = train_test_split(handspan, test_size=0.2, random_state=2)

    target = ['Sex']
    features = ['Height', 'HandSpan']

    X_train = train[features]
    X_test = test[features]
    y_train = train[target]
    y_test = test[target]

    model = LogisticRegression()
    model.fit(X_train, y_train)

    # 4)
    print(model.coef_)
    print(model.intercept_)

    print(model.score(X_test, y_test))

    # 5)
    y_pred = model.predict(X_test)

    # 6)
    def get_clf_eval(y_test, pred):
        confusion = confusion_matrix(y_test, pred)
        accuracy = accuracy_score(y_test, pred)
        precision = precision_score(y_test, pred, pos_label="Female")
        recall = recall_score(y_test, pred, pos_label="Female")
        f1 = f1_score(y_test, pred, pos_label='Female')
        print('오차 행렬')
        print(confusion)
        # f1 score print 추가
        print('정확도: {0:.4f}, 정밀도: {1:.4f}, 재현율: {2:.4f}, F1:{3:.4f}'.format(accuracy, precision, recall, f1))
        pred_proba = model.predict_proba(X_test)[:, 1]
        roc_score = roc_auc_score(y_test, pred_proba)
        print('ROC AUC 값: {0:.4f}'.format(roc_score))

    get_clf_eval(y_pred, y_test)


# PROB 3
def prob3():
    # 1)
    mpg_df = sns.load_dataset('mpg')
    print(mpg_df.isna().sum())
    mpg_df = mpg_df.dropna()

    # 3)
    train, test = train_test_split(mpg_df, test_size=0.2, random_state=2)

    target = ['origin']
    features = ['mpg', 'cylinders', 'displacement', 'horsepower', 'weight', 'acceleration', 'model_year']

    X_train = train[features]
    X_test = test[features]
    y_train = train[target]
    y_test = test[target]

    # 4)
    t = tree.DecisionTreeClassifier()
    t.fit(X_train, y_train)

    # 5)
    accuracy = accuracy_score(y_test, t.predict(X_test))
    print(format(accuracy, '.2f'))

    # 6)
    def finest(a, b):
        params = {
            'max_depth': [a, b],
            'min_samples_split': [a, b]
        }

        grid_tree = GridSearchCV(t, param_grid=params, cv=3, refit=True)
        grid_tree.fit(X_train, y_train)

        print('best parameters : ', grid_tree.best_params_)
        print('best score : ', grid_tree.best_score_)
        em = grid_tree.best_estimator_
        pred = em.predict(X_test)
        print(accuracy_score(y_test, pred))

    finest(2, 3)

    # 7, 8)
    finest(3, 5)
    finest(3, 4)

    finest(2, 5)
    finest(2, 4)  # best

    # 9)
    print(t.feature_importances_)
    plt.figure(figsize=(8, 4))
    plt.xlabel(features)
    plt.plot(t.feature_importances_)

    # 10)
    from sklearn.datasets import load_iris

    print(load_iris().target_names)
    print(load_iris().feature_names)
    print(target)
    print(features)
    tree.export_graphviz(t, out_file="tree.dot", class_names=['usa', 'europe', 'japan'],
                         feature_names=['mpg', 'cylinders', 'displacement', 'horsepower', 'weight', 'acceleration',
                                        'model_year'], impurity=True, filled=True)

    with open("tree.dot") as f:
        dot_graph = f.read()
    # print(graphviz.Source(dot_graph))


# PROB 4
def prob4():
    def modify(data):
        min_value = np.min(data)
        max_value = np.max(data)
        return (data - min_value) / (max_value - min_value)

    data = np.array([[14.0, 90.2, 90.95, 96.27, 91.21], [103.02, 107.26, 110.35, 114.23, 114.68]])
    print(modify(data))
    pass


# PROB 5
def prob5():
    '''
    최소-최대 정규화와 Z-점수 정규화의 차이점은 값이 생성되는 범위입니다. 최소-최대 정규화는 특정 범위에 속하는 값을 생성하는 반면, Z-점수 정규화는 평균이 0이고 표준 편차가 1인 값을 생성합니다.
    또 다른 차이점은 특이치를 처리하는 방식입니다. 최소-최대 정규화는 특이치가 값 범위를 왜곡할 수 있으므로 Z-점수 정규화만큼 특이치에 강하지 않습니다.
    '''
    pass


# PROB 6
def prob6():
    edges = pd.DataFrame(
        {'source': [0, 1, 2], 'target': [2, 2, 3], 'weight': [3, 4, 5], 'color': ['red', 'blue', 'blue']})
    print(pd.get_dummies(edges).iloc[:, 3:])
    print(pd.get_dummies(edges["color"]))
    print(pd.get_dummies(edges[["color"]]))
    print(pd.get_dummies(edges["color"], prefix="color"))
    pass


# PROB 7
def prob7():
    raw_data = {'first_name': ['Jason', np.nan, 'Tina', 'Jake', 'Amy'],
                'last_name': ['Miller', np.nan, 'Ali', 'Miner', 'Cooze'],
                'age': [42, np.nan, 36, 24, 73],
                'sex': ['m', np.nan, 'f', 'm', 'f'],
                'preTestScore': [4, np.nan, np.nan, 2, 3],
                'postTestScore': [42, np.nan, np.nan, 62, 70]}
    df = pd.DataFrame(raw_data, columns=['first_name', 'last_name', 'age', 'sex', 'preTestScore', 'postTestScore'])
    print(df.isnull().sum())

    pass


def prob8():
    # Yes, No
    a, b = 9, 5
    entropy_feature = -(log2(a / (a + b)) * (a / (a + b))) - (log2(b / (a + b)) * (b / (a + b)))

    # Overcast, Sunny, Rainy
    a, b, c = 4, 5, 5
    entropy_outlook = -(log2(a / (a + b + c)) * (a / (a + b + c))) - (log2(b / (a + b + c)) * (b / (a + b + c))) - (
            log2(c / (a + b + c)) * (c / (a + b + c)))

    # Hot, Mild, Cool
    a, b, c = 4, 6, 4
    entropy_temperature = -(log2(a / (a + b + c)) * (a / (a + b + c))) - (log2(b / (a + b + c)) * (b / (a + b + c))) - (
            log2(c / (a + b + c)) * (c / (a + b + c)))

    # High, Normal
    a, b = 7, 7
    entropy_humidity = -(log2(a / (a + b)) * (a / (a + b))) - (log2(b / (a + b)) * (b / (a + b)))

    # True, False
    a, b = 6, 8
    entropy_windy = -(log2(a / (a + b)) * (a / (a + b))) - (log2(b / (a + b)) * (b / (a + b)))

    print('entropy_outlook:', entropy_outlook)
    print('entropy_temperature:', entropy_temperature)
    print('entropy_humidity:', entropy_humidity)
    print('entropy_windy:', entropy_windy)
    print('entropy_feature:', entropy_feature)
