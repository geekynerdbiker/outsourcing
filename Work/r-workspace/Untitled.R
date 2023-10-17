library(randomForest)
library(caret)

# Load the data
##### 수정: 엑셀 파일을 불러오기 위한 함수 호출 및 헤드 열 건너뛰기
credit <- read_xls("defaul_of_credit_card_clients.xls", skip = 1)

##### 수정: "ID", "SEX", "EDUCATION", "MARRIAGE" 칼럼 제거
removeCols = c("ID", "SEX", "EDUCATION", "MARRIAGE")
credit = credit[, !(colnames(credit) %in% removeCols), drop = FALSE]

str(credit)
head(credit)
summary(credit)


# Split the data into a training set and a testing set
##### 수정: 시드 변경
set.seed(2128591)
train_index <- sample(nrow(credit), nrow(credit) * 0.8)
train <- credit[train_index, ]
test <- credit[-train_index, ]


# Train the random forest model
##### 수정: 학습 데이터를 토대로 PAY_0 ~ . 변수들(연체 상황) 예측
rf <- randomForest(PAY_0 ~ ., data = train, ntree = 1000)


# Predict using the model
predictions <- predict(rf, test)

# Convert predictions to factor, ensure levels match those in the test set
predictions <- as.factor(predictions)
levels(predictions) <- levels(test$PAY_6)

# Compute the confusion matrix
cm_rf <- confusionMatrix(predictions, test$PAY_6)

# Print the confusion matrix
print(cm_rf)

# Compute importance of each variable
importance <- importance(rf)

# Print the importance
print(importance)

# Plot importance of each variable
varImpPlot(rf)

##########################################################################

library(rpart)
library(rpart.plot)

##### 수정: 학습 데이터를 토대로 PAY_0 ~ . 변수들(연체 상황) 예측
tree_fit <- rpart(PAY_0 ~ ., 
                  data = train, 
                  method = "class",
                  control = rpart.control(minsplit = 1, cp = 0, maxdepth = 6))


# 결과확인
tree_fit

# 분류나무무
rpart.plot(tree_fit, yesno = 2, extra = 1, roundint = FALSE, varlen = 10)

# Make predictions using the rpart predict() function
predictions_rpart <- predict(tree_fit, newdata = test, type = "class")

cm_tree <- confusionMatrix(predictions_rpart, test$PAY_6)

# Print the confusion matrix
print(cm_tree)

###########################################################################

# Make sure you have the e1071 package installed and loaded
if (!require(e1071)) {
  install.packages("e1071")
  library(e1071)
}

# Train the SVM model
##### 수정: 학습 데이터를 토대로 PAY_0 ~ . 변수들(연체 상황) 예측
svm_model <- svm(PAY_0 ~ ., data = train, scale = T, kernel = "radial")

# Make predictions on the test set
predictions_svm <- predict(svm_model, newdata = test)

# Print out the confusion matrix
cm_svm <- confusionMatrix(predictions_svm, test$PAY_6)
print(cm_svm)

##############################################################################

# Install and load required packages
if (!require(kernlab)) install.packages('kernlab')
if (!require(caret)) install.packages('caret')
library(kernlab)
library(caret)

# Set the seed for reproducibility
set.seed(21285911)

# Define the training control
train_control <- trainControl(method = "cv", number = 10)  # 10-fold CV

tuneGrid <- expand.grid(C = seq(0.1, 1, by = 0.25),   # change as needed
                        sigma = c(0.01, 0.02, 0.03)) # change as needed
strftime(Sys.time(), "%H:%M:%S")


########################################################################
# Fit the logistic regression model
##### 수정: 학습 데이터를 토대로 PAY_0 ~ . 변수들(연체 상황) 예측
logit_model <- glm(PAY_0 ~ ., data = train, family = binomial(link = "logit"))

# Print the summary of the model
summary(logit_model)

# Make predictions on the test data
probabilities <- predict(logit_model, newdata = test, type = "response")

# Convert probabilities to class labels
predictions <- ifelse(probabilities > 0.5, "Male", "Female")

# Convert the predictions and the actual values to factors
predictions <- as.factor(predictions)
test$PAY_6 <- as.factor(test$PAY_6)

# Print the confusion matrix
cm_logit <- confusionMatrix(predictions, test$PAY_6)

print(cm_logit)
###########################################################################
#########################################################################
# Create a character vector of the names of your confusion matrix objects
library(dplyr)

cms <- c("cm_rf", "cm_tree", "cm_svm", "cm_logit")

# Use mget to get a list of the objects from their names
cm_list <- mget(cms)

# Compare the confusion matrices
comparison_result_wide <- compare_confusion_matrices_wide(cm_list)

# Remove row names from 'comparison_result'
rownames(comparison_result_wide) <- NULL

# Replace the 'Model' column with object names
comparison_result_wide$Model <- names(cm_list)

# Print 'comparison_result'
print(comparison_result_wide)

arrange(comparison_result_wide, desc(Sensitivity))
arrange(comparison_result_wide, desc(Specificity))


#################################################################################


comparison_result <- compare_confusion_matrices(cm_rf, cm_tree, cm_svm, cm_logit)
colnames(comparison_result) <- c("Metric", cms)
print(comparison_result)



##################################################################################
############# Confusion Matrix를 가로모드로 출력

compare_confusion_matrices_wide <- function(cm_list) {
  # Initialize a data frame to store the comparison results
  comparison_df <- data.frame(
    Model = character(),
    Accuracy = numeric(),
    Sensitivity = numeric(),
    Specificity = numeric(),
    Pos_Pred_Value = numeric(),
    Neg_Pred_Value = numeric(),
    F1_Score = numeric(),
    stringsAsFactors = FALSE
  )
  
  # Iterate through the list of confusion matrices
  for (i in seq_along(cm_list)) {
    cm <- cm_list[[i]]
    
    # Extract the relevant metrics
    model_name <- names(cm_list)[i]
    accuracy <- cm$overall["Accuracy"]
    sensitivity <- cm$byClass["Sensitivity"]
    specificity <- cm$byClass["Specificity"]
    pos_pred_value <- cm$byClass["Pos Pred Value"]
    neg_pred_value <- cm$byClass["Neg Pred Value"]
    f1_score <- 2 * (sensitivity * pos_pred_value) / (sensitivity + pos_pred_value)
    
    # Add the metrics to the comparison data frame
    comparison_df <- rbind(
      comparison_df,
      data.frame(
        Model = model_name,
        Accuracy = accuracy,
        Sensitivity = sensitivity,
        Specificity = specificity,
        Pos_Pred_Value = pos_pred_value,
        Neg_Pred_Value = neg_pred_value,
        F1_Score = f1_score
      )
    )
  }
  
  # Return the comparison data frame
  return(comparison_df)
}


###########################################################################
##################################################################################
############# Confusion Matrix를 세로모드로 출력

compare_confusion_matrices <- function(...) {
  cms <- list(...)
  metrics <- c("Accuracy", "Sensitivity", "Specificity", 
               "Pos Pred Value", "Neg Pred Value", "F1 Score")
  comparison_result <- data.frame(Metric = metrics)
  
  for (i in seq_along(cms)) {
    sensitivity <- cms[[i]]$byClass["Sensitivity"]
    specificity <- cms[[i]]$byClass["Specificity"]
    pos_pred_value <- cms[[i]]$byClass["Pos Pred Value"]
    neg_pred_value <- cms[[i]]$byClass["Neg Pred Value"]
    f1_score <- 2 * (sensitivity * pos_pred_value) / (sensitivity + pos_pred_value)
    
    model_metrics <- c(cms[[i]]$overall["Accuracy"], sensitivity, specificity, 
                       pos_pred_value, neg_pred_value, f1_score)
    col_name <- paste0("Model", i)
    comparison_result[col_name] <- model_metrics
  }
  
  return(comparison_result)
}

