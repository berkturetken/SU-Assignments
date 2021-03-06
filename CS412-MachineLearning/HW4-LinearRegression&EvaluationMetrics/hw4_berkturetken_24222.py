# -*- coding: utf-8 -*-
"""HW4_berkturetken_24222.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1vku4WptGC0UZ41ZI_K5Xf0mkWvC_6o49

# Load the dataset
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt                   

df = pd.read_csv('https://raw.githubusercontent.com/OpenClassrooms-Student-Center/Evaluate-Improve-Models/master/house_prices.csv')
df.sample(5)

"""# "Garage Area" and "SalesPrice" features are selected to analyze."""

new_df = df[['Garage Area', 'SalesPrice']]

"""## Convert the data into numpy arrays of two variables, X and y."""

X = np.array(new_df[['Garage Area']])
y = np.array(new_df[['SalesPrice']]) 
print(X.shape)
print(y.shape)

"""## Split train and test data with 0.2 ratio."""

from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2)

"""# Linear Regression
Train a linear regression.
"""

from sklearn import linear_model 

regressor = linear_model.LinearRegression()
regressor.fit(X_train, y_train)

"""## Calculate train and test R2."""

from sklearn.metrics import r2_score

y_train_prediction = regressor.predict(X_train)
print("Train:", r2_score(y_train, y_train_prediction))

y_test_prediction = regressor.predict(X_test)
print("Test:", r2_score(y_test, y_test_prediction))

"""## Print the bias and the slope."""

print('Regressor coeffient or slope:', regressor.coef_[0][0])
print('Interception point with axis:', regressor.intercept_[0])

"""## Plot the test set with scatter plot and add the linear regression model line.
Remember linear regression recitation.
"""

plt.scatter(X_test, y_test, color="green")
y_train_prediction = regressor.predict(X_train)
plt.plot(X_train, y_train_prediction, color="red", linewidth=3)
plt.title('Regression(Test Set)')
plt.xlabel('Garage Area')
plt.ylabel('Sales Price')
plt.show()

"""# Multiple Linear Regression
Select all features.
"""

X = df.iloc[:, 0:304] 
y = df[['SalesPrice']]
print(X.shape)
print(y.shape)

"""## Rescale the input features. Use MinMaxScaler."""

from sklearn.preprocessing import MinMaxScaler
scaler = MinMaxScaler()
X = scaler.fit_transform(X)

"""## Train test split."""

x_train, x_test, y_train, y_test = train_test_split(X, y, test_size = 0.2)

"""## Fit regression model."""

multiple_regressor = linear_model.LinearRegression()
multiple_regressor.fit(x_train, y_train)

"""## Calculate train and test R2."""

y_train_prediction = multiple_regressor.predict(x_train)
print("Train:", r2_score(y_train, y_train_prediction))

y_test_prediction = multiple_regressor.predict(x_test)
print("Test:", r2_score(y_test, y_test_prediction))

"""## Print the regression coefficients."""

print('Regressor coeffients for multiple linear regression:', multiple_regressor.coef_[0])

"""# Ridge Regression
https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.KFold.html

https://scikit-learn.org/stable/modules/generated/sklearn.linear_model.RidgeCV.html

## Use cross-validation to estimate alpha. Set the fold size to 5.
"""

from sklearn.model_selection import KFold
from sklearn.linear_model import RidgeCV
kfold = KFold(n_splits=5)

alphas=[1e-3, 1e-2, 1e-1, 1, 2, 5, 8, 10]
model_rcv = RidgeCV(alphas=alphas, cv=kfold)
model_rcv.fit(x_train, y_train)

"""## Calculate the train and test R2."""

y_train_prediction = model_rcv.predict(x_train)
print("Train:", r2_score(y_train, y_train_prediction))

y_test_prediction = model_rcv.predict(x_test)
print("Test:", r2_score(y_test, y_test_prediction))

"""## Print the best alpha."""

print("Alpha:", model_rcv.alpha_)

"""## Print the regression coefficients."""

print('Regressor coeffients for ridge regression:', model_rcv.coef_[0])