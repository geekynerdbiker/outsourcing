package ssu.btetris.singleuser;

import java.io.Serializable;

import ssu.btetris.model.*;

public class JTetrisModel implements Serializable {
    private final JTetris board;

    public Matrix getBlock(char type) {
        return JTetris.setOfBlockObjects[type - '0'][0];
    }

    public Matrix getScreen() {
        return board.get_oScreen();
    }

    public JTetrisModel(int dy, int dx) throws Exception {
        // [7][4][?][?]
        // end of arrayBlock
        int[][][][] setOfBlockArrays = { // [7][4][?][?]
                {
                        {
                                {0, 2, 0},
                                {0, 3, 0},
                                {0, 4, 0}
                        },
                        {
                                {0, 0, 0},
                                {4, 3, 2},
                                {0, 0, 0}
                        },
                        {
                                {0, 4, 0},
                                {0, 3, 0},
                                {0, 2, 0}
                        },
                        {
                                {0, 0, 0},
                                {2, 3, 4},
                                {0, 0, 0}
                        }
                },
                {
                        {
                                {0, 2, 0},
                                {0, 2, 0},
                                {0, 3, 0}
                        },
                        {
                                {0, 0, 0},
                                {3, 2, 2},
                                {0, 0, 0}
                        },
                        {
                                {0, 3, 0},
                                {0, 2, 0},
                                {0, 2, 0}
                        },
                        {
                                {0, 0, 0},
                                {2, 2, 3},
                                {0, 0, 0}
                        }
                },
                {
                        {
                                {0, 3, 0},
                                {0, 3, 0},
                                {0, 4, 0}
                        },
                        {
                                {0, 0, 0},
                                {4, 3, 3},
                                {0, 0, 0}
                        },
                        {
                                {0, 4, 0},
                                {0, 3, 0},
                                {0, 3, 0}
                        },
                        {
                                {0, 0, 0},
                                {3, 3, 4},
                                {0, 0, 0}
                        }
                },
                {
                        {
                                {0, 4, 0},
                                {0, 2, 0},
                                {0, 4, 0}
                        },
                        {
                                {0, 0, 0},
                                {4, 2, 4},
                                {0, 0, 0}
                        },
                        {
                                {0, 4, 0},
                                {0, 2, 0},
                                {0, 4, 0}
                        },
                        {
                                {0, 0, 0},
                                {4, 2, 4},
                                {0, 0, 0}
                        }
                },
                {
                        {
                                {0, 3, 0},
                                {0, 4, 0},
                                {0, 3, 0}
                        },
                        {
                                {0, 0, 0},
                                {3, 4, 3},
                                {0, 0, 0}
                        },
                        {
                                {0, 3, 0},
                                {0, 4, 0},
                                {0, 3, 0}
                        },
                        {
                                {0, 0, 0},
                                {3, 4, 3},
                                {0, 0, 0}
                        }
                },
                {
                        {
                                {0, 4, 0},
                                {0, 4, 0},
                                {0, 2, 0}
                        },
                        {
                                {0, 0, 0},
                                {2, 4, 4},
                                {0, 0, 0}
                        },
                        {
                                {0, 2, 0},
                                {0, 4, 0},
                                {0, 4, 0}
                        },
                        {
                                {0, 0, 0},
                                {4, 4, 2},
                                {0, 0, 0}
                        }
                },
                {
                        {
                                {0, 3, 0},
                                {0, 2, 0},
                                {0, 4, 0}
                        },
                        {
                                {0, 0, 0},
                                {4, 2, 3},
                                {0, 0, 0}
                        },
                        {
                                {0, 4, 0},
                                {0, 2, 0},
                                {0, 3, 0}
                        },
                        {
                                {0, 0, 0},
                                {3, 2, 4},
                                {0, 0, 0}
                        }
                }
        };
        JTetris.init(setOfBlockArrays);
        board = new JTetris(dy, dx);
    }

    public JTetris.TetrisState accept(char ch) throws Exception {
        return board.accept(ch);
    }
}

