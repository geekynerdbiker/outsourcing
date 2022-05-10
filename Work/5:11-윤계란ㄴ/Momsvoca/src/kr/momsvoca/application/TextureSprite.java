package kr.momsvoca.application;

import com.GoldenMine.graphic.elements.sprite.ObjectSprite;
import com.GoldenMine.graphic.elements.textures.Texture;

public class TextureSprite {
    private Texture texture;
    private ObjectSprite sprite;

    //boolean created;

    public TextureSprite() {

    }

    public void setTexture(Texture texture) {
        if(sprite == null)
            this.texture = texture;
        else
            throw new RuntimeException("cannot edit after getSprite() is called");
    }

    public Texture getTexture() {
        return texture;
    }

    public ObjectSprite getSprite() {
        if(sprite == null) {
            sprite = new ObjectSprite(texture);
        }
        return sprite;
    }
}
