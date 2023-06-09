[top]
components : warehouse@Warehouse manufacturer transportation@Transportation
out : out1
out : out2
out : out3
in : in
Link : in win1@warehouse
Link : wout1@warehouse  tin@transportation
Link : tout2@transportation  win3@warehouse
Link : tout1@transportation  min@manufacturer
Link : mout2@manufacturer  win2@warehouse
Link : mout2@manufacturer  out2
Link : wout2@warehouse  out3
Link : mout1@manufacturer  out1


[manufacturer]
components : preprocessing@Preprocessing assembling@Assembling
out : mout1
out : mout2
in : min
Link : min pin1@preprocessing
Link : pout1@preprocessing    ain@assembling
Link : aout2@assembling  pin2@preprocessing
Link : aout1@assembling  mout1
Link : pout2@preprocessing  mout2