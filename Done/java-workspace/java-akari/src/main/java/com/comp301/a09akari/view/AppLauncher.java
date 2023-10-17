package com.comp301.a09akari.view;

import com.comp301.a09akari.testCase;
import com.comp301.a09akari.controller.ControllerImpl;
import com.comp301.a09akari.model.*;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class AppLauncher extends Application {
  @Override
  public void start(Stage stage) {
    // TODO: Create your Model, View, and Controller instances and launch your GUI

    PuzzleLibrary plib = new PuzzleLibraryImpl();
    plib.addPuzzle(new PuzzleImpl(testCase.PUZZLE_01));
    plib.addPuzzle(new PuzzleImpl(testCase.PUZZLE_02));
    plib.addPuzzle(new PuzzleImpl(testCase.PUZZLE_03));
    plib.addPuzzle(new PuzzleImpl(testCase.PUZZLE_04));
    plib.addPuzzle(new PuzzleImpl(testCase.PUZZLE_05));

    Model model = new ModelImpl(plib);
    ControllerImpl controller = new ControllerImpl(model);
    AppView appView = new AppView(model, controller);

    Scene scene = new Scene(appView.render());
    scene.getStylesheets().add("main.css");
    stage.setScene(scene);

    model.addObserver(
        (Model m) -> {
          scene.setRoot(appView.render());
          stage.sizeToScene();
        });

    stage.setTitle("Akari");
    stage.show();


  }
}
