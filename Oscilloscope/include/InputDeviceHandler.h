#ifndef INPUTDEVICEHANDLER_H_
#define INPUTDEVICEHANDLER_H_

#define PIN_JOY_FIRE  PB6

enum InputDeviceEvent
{
	// simple states
	JOY_NONE=0,
	JOY_UP=1,
	JOY_RIGHT=2,
	JOY_DOWN=4,
	JOY_LEFT=8,
	JOY_FIRE=16,
	JOY_REPEAT=32,
	JOY_DOUBLE_FIRE=80,

	// composite states
	JOY_UPLEFT=JOY_UP+JOY_LEFT,
	JOY_UPRIGHT=JOY_UP+JOY_RIGHT,
	JOY_DOWNLEFT=JOY_DOWN+JOY_LEFT,
	JOY_DOWNRIGHT=JOY_DOWN+JOY_RIGHT,

	JOY_FIRE_UP=JOY_FIRE+JOY_UP,
	JOY_FIRE_UPLEFT=JOY_FIRE+JOY_UP+JOY_LEFT,
	JOY_FIRE_UPRIGHT=JOY_FIRE+JOY_UP+JOY_RIGHT,
	JOY_FIRE_DOWN=JOY_FIRE+JOY_DOWN,
	JOY_FIRE_DOWNLEFT=JOY_FIRE+JOY_DOWN+JOY_LEFT,
	JOY_FIRE_DOWNRIGHT=JOY_FIRE+JOY_DOWN+JOY_RIGHT,
	JOY_FIRE_LEFT=JOY_FIRE+JOY_LEFT,
	JOY_FIRE_RIGHT=JOY_FIRE+JOY_RIGHT,

	JOY_REPEAT_FIRE=JOY_REPEAT+JOY_FIRE,

	JOY_REPEAT_UP=JOY_REPEAT+JOY_UP,
	JOY_REPEAT_UPLEFT=JOY_REPEAT+JOY_UP+JOY_LEFT,
	JOY_REPEAT_UPRIGHT=JOY_REPEAT+JOY_UP+JOY_RIGHT,
	JOY_REPEAT_DOWN=JOY_REPEAT+JOY_DOWN,
	JOY_REPEAT_DOWNLEFT=JOY_REPEAT+JOY_DOWN+JOY_LEFT,
	JOY_REPEAT_DOWNRIGHT=JOY_REPEAT+JOY_DOWN+JOY_RIGHT,
	JOY_REPEAT_LEFT=JOY_REPEAT+JOY_LEFT,
	JOY_REPEAT_RIGHT=JOY_REPEAT+JOY_RIGHT,

	JOY_REPEAT_FIRE_UP=JOY_REPEAT+JOY_FIRE+JOY_UP,
	JOY_REPEAT_FIRE_UPLEFT=JOY_REPEAT+JOY_FIRE+JOY_UP+JOY_LEFT,
	JOY_REPEAT_FIRE_UPRIGHT=JOY_REPEAT+JOY_FIRE+JOY_UP+JOY_RIGHT,
	JOY_REPEAT_FIRE_DOWN=JOY_REPEAT+JOY_FIRE+JOY_DOWN,
	JOY_REPEAT_FIRE_DOWNLEFT=JOY_REPEAT+JOY_FIRE+JOY_DOWN+JOY_LEFT,
	JOY_REPEAT_FIRE_DOWNRIGHT=JOY_REPEAT+JOY_FIRE+JOY_DOWN+JOY_RIGHT,
	JOY_REPEAT_FIRE_LEFT=JOY_REPEAT+JOY_FIRE+JOY_LEFT,
	JOY_REPEAT_FIRE_RIGHT=JOY_REPEAT+JOY_FIRE+JOY_RIGHT,

	USB_COMMAND_NONE=0,
	USB_COMMAND_START_TRANSMISSION=0x1000,
};

typedef void (*InputDeviceCallback)(InputDeviceEvent event);

class InputDeviceHandler
{
private:
	InputDeviceCallback inputDeviceCallback = 0;
	unsigned            lastJoyEventStamp = 0xF0000000;
	unsigned            lastJoyReadStamp = 0;
	InputDeviceEvent    lastEvent = JOY_NONE;
	unsigned            doubleFireCounter = 0xFFFFFFFF;
	InputDeviceEvent    usbEvent = USB_COMMAND_NONE;

	InputDeviceEvent    readJoystickState(unsigned time);

public:
	void                init(InputDeviceCallback cb=0);
	void                loop();

	InputDeviceCallback getInputDeviceCallback() { return inputDeviceCallback; }
	void                setInputDeviceCallback( InputDeviceCallback cb ) { inputDeviceCallback = cb; }

	void                noJoystickData();
	void                setUSBCommand(InputDeviceEvent event) {usbEvent = event;}
};

extern InputDeviceHandler inputDeviceHandler;

#endif /* INPUTDEVICEHANDLER_H_ */
