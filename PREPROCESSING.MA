[top]
components : preprocessing@Preprocessing
out : pout1
out : pout2
in : pin1
in : pin2 
Link : pin1 pin1@preprocessing
Link : pin2 pin2@preprocessing
Link : pout1@preprocessing pout1
Link : pout2@preprocessing pout2