library(shiny)
library(ggplot2)
library(rsconnect)
library(palmerpenguins)
library(tidyverse)
library(DT)

data("penguins")

variables <- c("bill_length_mm",
             "bill_depth_mm",
             "flipper_length_mm",
             "body_mass_g")

ui <-fluidPage(
  headerPanel('Penguin data analyze'),
  sidebarPanel(
    checkboxGroupInput('xcol', 'Select species', unique(penguins$species)),
    selectInput('xcol', 'X Variables', variables),
    selectInput('ycol', 'Y Variables', variables, variables[4]),
    sliderInput('pointSize','Size of Point',min = 1, max = 10, value = 5)
  ),
  mainPanel(
    DT::dataTableOutput("table"),
    plotOutput(outputId = "plot")
  )
)

server <- function(input, output) { 
  output$table = DT::renderDataTable({
    penguins
  })
  output$plot <- renderPlot({
    ggplot(penguins, aes_string(x = input$xcol, y = input$ycol, color=penguins$species, shape=penguins$sex)) +
      geom_point()
  })
}
shinyApp(ui = ui, server = server)