# based on https://docs.odriverobotics.com/hoverboard.html
import odrive
import time

motor_calibration_time = 6
encoder_calibration_time = 12

input("Make sure that the wheels are free to turn. Don't get hurt!\nPress ENTER to proceed.")

print("Searching for ODrive...")
odrv0 = odrive.find_any()
print("Odrive detected!")

print("--------------Motor Calibration--------------------------------")
print("Calibrating motors...")
odrv0.axis0.requested_state = 4 # AXIS_STATE_MOTOR_CALIBRATION
odrv0.axis1.requested_state = 4 # AXIS_STATE_MOTOR_CALIBRATION
time.sleep(motor_calibration_time)
if odrv0.axis0.motor.is_calibrated == 1 and odrv0.axis1.motor.is_calibrated == 1:
	print("Motor successfully calibrated! Proceeding...")
else:
	print("Could not calibrate motor. Something is wrong.")
	print("Have you ran the first script to set all parameters?")
	print("If yes and the wiring looks good, reset the ODrive and try again.\nExiting.")
	quit()
print("Saving motor calibration")
odrv0.axis0.motor.config.pre_calibrated = True
odrv0.axis1.motor.config.pre_calibrated = True
print("--------------Encoder calibration------------------------------")
print("Calibrating encoder offset...")
odrv0.axis0.requested_state = 7 # AXIS_STATE_ENCODER_OFFSET_CALIBRATION
odrv0.axis1.requested_state = 7 # AXIS_STATE_ENCODER_OFFSET_CALIBRATION
time.sleep(encoder_calibration_time)
if odrv0.axis0.encoder.is_ready == 1 and odrv0.axis1.encoder.is_ready == 1:
	print("Encoder offset successfully calibrated! Proceeding...")
else:
	print("Could not calibrate encoder offset. Something is wrong.")
	print("Have you ran the first script to set all parameters?")
	print("If yes and the wiring looks good, reset the ODrive and try again.\nExiting.")
	quit()
print("Saving encoder offset calibration")	
odrv0.axis0.encoder.config.pre_calibrated = True
odrv0.axis1.encoder.config.pre_calibrated = True
print("--------------Save and reboot----------------------------------")
odrv0.save_configuration()
try:
	odrv0.reboot()
except:
	print("USB connection crashes during reboot - that is to be expected.") 
	print("Probably all is good.")
	print("The ODrive is now ready to be used in HoverBot!")
