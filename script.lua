local device = Device.open(0)
if device == nil then
	print("NOT GOOD")
	os.exit(1)
end

Device.interactive_mode(device)

Device.close(device)
