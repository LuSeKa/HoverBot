import odrive

# Paramters for HoverBot. Probalby no need to change.
pole_pairs = 15
resistance_calib_max_voltage = 4
requested_current_range = 25
current_control_bandwidth = 100
cpr = pole_pairs * 6
encoder_bandwidth = 100
vel_limit = 1000

print("Searching for ODrive...")
odrv0 = odrive.find_any()
print("Odrive detected!")
print("-------------Motor parameters----------------------------------")
print("Setting number of pole pairs to {}".format(pole_pairs))
odrv0.axis0.motor.config.pole_pairs = pole_pairs
odrv0.axis1.motor.config.pole_pairs = pole_pairs
print("Setting maximum calibration voltage to {}".format(resistance_calib_max_voltage))
odrv0.axis0.motor.config.resistance_calib_max_voltage = resistance_calib_max_voltage
odrv0.axis1.motor.config.resistance_calib_max_voltage = resistance_calib_max_voltage
print("Setting current range to {}".format(requested_current_range))
odrv0.axis0.motor.config.requested_current_range = requested_current_range
odrv0.axis1.motor.config.requested_current_range = requested_current_range
print("Setting current control bandwidth to {}".format(current_control_bandwidth))
odrv0.axis0.motor.config.current_control_bandwidth = current_control_bandwidth
odrv0.axis1.motor.config.current_control_bandwidth = current_control_bandwidth
print("--------------Encoder parameters-------------------------------")
print("Configuring for hall encoders")
odrv0.axis0.encoder.config.mode = 1 # ENCODER_MODE_HALL
odrv0.axis1.encoder.config.mode = 1 # ENCODER_MODE_HALL
print("Setting encoder resolution to {}".format(cpr))
odrv0.axis0.encoder.config.cpr = cpr
odrv0.axis1.encoder.config.cpr = cpr
print("--------------Controller parameters----------------------------")
print("Setting encoder bandwidth to {}".format(encoder_bandwidth))
odrv0.axis0.encoder.config.bandwidth = encoder_bandwidth
odrv0.axis1.encoder.config.bandwidth = encoder_bandwidth
print("Setting velocity limit to {}".format(vel_limit))
odrv0.axis0.controller.config.vel_limit = vel_limit
odrv0.axis1.controller.config.vel_limit = vel_limit
print("Configuring for current control")
odrv0.axis0.controller.config.control_mode = 1 #CTRL_MODE_CURRENT_CONTROL
odrv0.axis1.controller.config.control_mode = 1 #CTRL_MODE_CURRENT_CONTROL
print("--------------Save and reboot----------------------------------")
odrv0.save_configuration()
try:
	odrv0.reboot()
except:
	print("USB connection crashes during reboot - that is to be expected.") 
	print("Probably all is good.")
	print("Proceed to next script to get the motors spinning!")
