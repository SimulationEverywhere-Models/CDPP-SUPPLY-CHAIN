[top]
components : preprocessing@Preprocessing assembling@Assembling
out : mout1
out : mout2
in : min
Link : min pin1@preprocessing
Link : pout1@preprocessing    ain@assembling
Link : aout2@assembling  pin2@preprocessing
Link : aout1@assembling  mout1
Link : pout2@preprocessing  mout2