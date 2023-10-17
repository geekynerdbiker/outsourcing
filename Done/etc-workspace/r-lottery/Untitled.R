# Load packages
library('ggplot2') # visualization
library('ggthemes') # visualization
library('scales') # visualization
library('dplyr') # data manipulation
library('randomForest') # classification algorithm

# Reading the data set (lottery-train.csv)
train <- read.csv('./lottery-train-2023-2-1.csv', stringsAsFactors = F) # STEP 1: Split the data set into two parts: 'train' and 'test'

# your train data should be more 70% of the given data set
# show your code below
# e.g.) full[1:1500,]
train$id <- 1:nrow(train)
df_train <- train %>% dplyr::sample_frac(0.70)
df_test  <- dplyr::anti_join(train, df_train, by = 'id')

train = df_train
test = df_test

# Display your datasets. Do Not Delete.
str(train)
str(test)

# Build a random forest mode
# STEP 2-1: Set a random seed
# show your code below
set.seed(1)

# STEP 2-2: Build your random forest model
# You are free to choose your selection of available feature.
# See more detailed explanation in the midterm instruction.
# Identify your target feature to predict and the rest.
# BONUS: If you have your own feature to add, make one and use it in your code.
# Explain your feature here (add comments).
# show your code below
# e.g.) randomForest(factor(?) ~ ? + ?, data = ?)
your_model <- randomForest(factor(win) ~ third + fourth, data = train)

# STEP 3: Show model error, calculate importance, and rank valuable. Draw figures.
# STEP 3-1: Show model error and plot it.
# Your output figures should be close to the examples in the midterm instruction. # show your code below
plot(your_model)

# STEP 3-2: Calcuate importance
# show your code below
importance(your_model)

# STEP 3-3: Create a rank variable based on importance. And use ggplot to draw figures as in the midterm instruction.
# show your code below
var_importance <- data_frame(variable=row.names(importance(your_model)), importance=as.vector(importance(your_model)))
var_importance <- arrange(var_importance, desc(importance))
var_importance$variable <- factor(var_importance$variable, levels=var_importance$variable)

ggplot(var_importance, aes(x=importance, y=variable, fill=importance)) + geom_bar(stat = 'identity')

# Prediction using your_model against test data. Do Not Delete.# Prediction using your_modclass()el against test data. Do Not Delete.
prediction <- predict(your_model, test)
# STEP 4: Caculate solution (using prediction above) and save it to 'lottery-solution.csv' where it contain the two columns: round and win.
# show your code below
prediction = as.data.frame(prediction[1:20])
prediction
write.csv(prediction, file='lottery-solution.csv')

