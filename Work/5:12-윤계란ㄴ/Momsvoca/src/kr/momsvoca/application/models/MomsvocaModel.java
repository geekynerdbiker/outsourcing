package kr.momsvoca.application.models;

import kr.momsvoca.application.WordStorage;

import java.util.HashMap;

public class MomsvocaModel {
    MomsvocaTitleModel titleModel;
    MomsvocaSinglePlayModel singlePlayModel;

    HashMap<String, WordStorage> wordStorages = new HashMap<>();

    //public TextTexture test;
    //public ObjectSprite sprite;



    public MomsvocaModel() {
        
    }

    public void initialize() {
        titleModel = new MomsvocaTitleModel();
        titleModel.initalize();
        initalizeWordStorage();
        singlePlayModel = new MomsvocaSinglePlayModel(wordStorages);
        singlePlayModel.initialize();
    }

    public void initalizeWordStorage() {
        wordStorages.put("middle", new WordStorage("resources/words/middle"));
        wordStorages.put("high", new WordStorage("resources/words/high"));
        wordStorages.put("everyday", new WordStorage("resources/words/everyday"));
    }



    /*
    public Texture getMainTitleTexture() {
        return mainTitleTexture;
    }

    public Texture getSinglePlayTexture() {
        return singlePlayTexture;
    }

    public Texture getSinglePlayTextureClicked() {
        return singlePlayTextureClicked;
    }

    public Texture getMultiPlayTexture() {
        return multiPlayTexture;
    }

    public Texture getMultiPlayTextureClicked() {
        return multiPlayTextureClicked;
    }

    public Texture getTutorialTexture() {
        return tutorialTexture;
    }

    public Texture getTutorialTextureClicked() {
        return tutorialTextureClicked;
    }

    public Texture getSinglePlayMiddleSelectTexture() {
        return singlePlayMiddleSelectTexture;
    }

    public Texture getSinglePlayHighSelectTexture() {
        return singlePlayHighSelectTexture;
    }

    public Texture getSinglePlayEverydaySelectTexture() {
        return singlePlayEverydaySelectTexture;
    }*/




    public HashMap<String, WordStorage> getWordStorages() {
        return wordStorages;
    }

    public MomsvocaTitleModel getTitleModel() {
        return titleModel;
    }

    public MomsvocaSinglePlayModel getSinglePlayModel() {
        return singlePlayModel;
    }
}
