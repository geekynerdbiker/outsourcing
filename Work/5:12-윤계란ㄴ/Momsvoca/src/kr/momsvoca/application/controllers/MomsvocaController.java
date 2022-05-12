package kr.momsvoca.application.controllers;

import kr.momsvoca.application.MomsvocaView;
import kr.momsvoca.application.models.MomsvocaModel;

public class MomsvocaController {

    MomsvocaModel model;
    MomsvocaView view;

    MomsvocaSinglePlayController vocaController;

    public MomsvocaController(MomsvocaModel model, MomsvocaView view) {
        this.model = model;
        this.view = view;

        vocaController = new MomsvocaSinglePlayController(model, view);
    }

    /*public void disableAllFolders() {
        view.singlePlayMiddleFolderGroup.setEnabled(false);
        view.singlePlayHighFolderGroup.setEnabled(false);
        view.singlePlayEverydayFolderGroup.setEnabled(false);
        view.singlePlayMiddleFolderGroup.setOpacity(0);
        view.singlePlayHighFolderGroup.setOpacity(0);
        view.singlePlayEverydayFolderGroup.setOpacity(0);
    }*/

    public void initialize() {
        initalizeMainTitle();

        vocaController.initialize();
    }


    public void initalizeMainTitle() {
        model.getTitleModel().getSinglePlaySprite().getSprite().addButtonClickedEvent(clicked -> {
            if (clicked) {
                view.titleGroupFinish();
                view.singlePlayGroupStart(null);

                //singlePlayTapGroup.addEffects(new EffectFader(), new Interval(60, 120, new CalculateModelNaturalSin()), 0f, 1f);
                //singlePlaySelectMiddleGroup.addEffects(new EffectFader(), new Interval(60, 120, new CalculateModelNaturalSin()), 0f, 1f);
            }
        });

        model.getTitleModel().getMultiPlaySprite().getSprite().addButtonClickedEvent(clicked -> {
            if (clicked) {
                view.titleGroupFinish();
                view.multiPlayGroupStart();
                //singlePlayTapGroup.addEffects(new EffectFader(), new Interval(60, 120, new CalculateModelNaturalSin()), 0f, 1f);
                //singlePlaySelectMiddleGroup.addEffects(new EffectFader(), new Interval(60, 120, new CalculateModelNaturalSin()), 0f, 1f);
            }
        });

        model.getTitleModel().getTutorialSprite().getSprite().addButtonClickedEvent(clicked -> {
            if (clicked) {
                view.titleGroupFinish();
                view.tutorialGroupStart();
                //singlePlayTapGroup.addEffects(new EffectFader(), new Interval(60, 120, new CalculateModelNaturalSin()), 0f, 1f);
                //singlePlaySelectMiddleGroup.addEffects(new EffectFader(), new Interval(60, 120, new CalculateModelNaturalSin()), 0f, 1f);
            }
        });
    }


}
