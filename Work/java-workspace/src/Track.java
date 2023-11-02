public class Track {
    // 게임 선택 창 표지 이미지
    private String startImage;
    // 해당 곡을 실행했을 때 표지 이미지
    private String gameImage;
    // 게임 선택 창 음악
    private String startMusic;
    // 해당 곡을 실행했을 때 음악
    private String gameMusic;
    // 해당 곡의 제목
    private String titleName;

    // 시작 이미지 반환
    public String getStartImage() {
        return startImage;
    }

    // 인게임 이미지 반환
    public String getGameImage() {
        return gameImage;
    }

    // 타이틀 반환
    public String getTitleName() {
        return titleName;
    }

    // 생성자
    public Track(String startImage, String gameImage, String titleName, String startMusic, String gameMusic) {
        super();
        this.startImage = startImage;
        this.gameImage = gameImage;
        this.titleName = titleName;
        this.startMusic = startMusic;
        this.gameMusic = gameMusic;
    }

    // 시작 음악 파일명 반환
    public String getStartMusic() {
        return startMusic;
    }

    // 인게임 음악 파일명 반환
    public String getGameMusic() {
        return gameMusic;
    }
}
