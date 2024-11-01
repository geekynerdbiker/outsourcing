#ifndef _PROJECTS_PROJECT1_AW_MESSAGE_H__
#define _PROJECTS_PROJECT1_AW_MESSAGE_H__

typedef enum Command {
    /** move up */
    CMD_UP = 0,
    /** move down */
    CMD_DOWN,
    /** move left */
    CMD_LEFT,
    /** move right */
    CMD_RIGHT,
    /** do nothing */
    CMD_NOP
} Command;

/**
 * For easy to implement, combine robot and central control node message
 * If you want to modify message structure, don't split it
 */
typedef struct Message {
    //
    // To central control node
    //
    /** current row of robot */
    int row;
    /** current column of robot */
    int col;
    /** current payload of robot */
    int current;
    /** required paylod of robot */
    int required;

    //
    // To robots
    //
    /** next command for robot */
    Command cmd;
} Message;

/** 
 * Simple message box which can receive only one message from sender
*/
typedef struct MesssageBox {
    /** check if the message was written by others */
    int dirtyBit;
    /** stored message */
    Message msg;
} MesssageBox;

/** message boxes from central control node to each robot */
extern MesssageBox* boxes_from_node;
/** message boxes from robots to central control node */
extern MesssageBox* boxes_from_robots;

int NUM_ROBOTS;

typedef enum MessageEndpoint {
    ROBOT,
    CENTRAL_CONTROL
} MessageEndpoint;

int send(int robotIdx, Message* msg, MessageEndpoint endpoint);
int receive(int robotIdx, Message* msg, MessageEndpoint direction);

/** initialize message boxes */
int initialize_message_boxes(int num_robots);

void set_command(Message* msg, Command cmd);

#endif