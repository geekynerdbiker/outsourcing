import q4


def main():
    q4.intro()
    q4.travel_to_camp()

    while True:
        setup = q4.setup_trap('')
        horn_input = q4.sound_horn('')
        hunt_status = q4.basic_hunt(setup[1], horn_input)
        q4.end(hunt_status)

        training = input('\nPress Enter to continue training and "no" to stop training: ')
        if training == 'no':
            return setup

        else:
            continue


if __name__ == '__main__':
    main()
