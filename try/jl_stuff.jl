const SO_FILE::String = "./build/libNSCA1_stepper_motor_control.so"

mutable struct Device
    libusb_context::Ref{Cvoid}
    libusb_device_handle::Ref{Cvoid}
    iface_number::Cint
end


function open_device()::Device
    device = Device(Ref{Nothing}(), Ref{Nothing}(), 0)
    result = @ccall SO_FILE.open_device(Ref{Device}(device)::Ref{Device})::Cint
    if result != 0
        println("Couldn't open device")
    end
    return device
end


function close_device()::Device
    device = Device(Ref{Nothing}(), Ref{Nothing}(), 0)
    result = @ccall SO_FILE.close_device(Ref{Device}(device)::Ref{Device})::Cint
    if result != 0
        println("Couldn't close device")
    end
    return device
end
