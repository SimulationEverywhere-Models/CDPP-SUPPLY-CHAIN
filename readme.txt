
NOTE: ALL TESTING STRATEGIES AND DETAILED BEHAVIOR FOR EACH CASE ARE DESCRIBED 
IN THE SCOM SIMULATION REPORT. 

The corresponding MA files for these models are labelled as SCOM.MA, MANUFACTURER.MA,
WAREHOUSE.MA, TRANSPORTATION.MA, PREPROCESSING.MA, and ASSEMBLING.MA.

The corresponding scripts for testing these models are listed as follows:
SCOM Model:
  SCOM_case1.bat -> testing for case1
  SCOM_case2.bat -> testing for case2
Manufacturer Model:
   MANUFACTURER.bat,
Warehouse Model:
   WAREHOUSE_case1.bat -> testing for case1
   WAREHOUSE_case2.bat -> testing for case2
   WAREHOUSE_case3.bat -> testing for case3
Transportation Model:   
   TRANSPORTATION.bat
Preprocessing Model:
   PREPROCESSING.bat 
Assembling Model:   
   ASSEMBLING.bat

The corresponding EV files for testing these models are listed as follows:
SCOM Model:
   SCOM_case1.EV -> testing for case1
   SCOM_case2.EV -> testing for case2
Manufacturer Model:
   MANUFACTURER.EV,
Warehouse Model:
   WAREHOUSE_case1.EV -> testing for case1
   WAREHOUSE_case2.EV -> testing for case2
   WAREHOUSE_case3.EV -> testing for case3
Transportation Model:   
   TRANSPORTATION.EV 
Preprocessing Model:
   PREPROCESSING.EV 
Assembling Model:   
   ASSEMBLING.EV

The corresponding LOG files for these models are listed as follows:
SCOM Model:
   SCOM_case1.log -> testing result of case1
   SCOM_case2.log -> testing result of case2
Manufacturer Model:
   MANUFACTURER.log,
Warehouse Model:
   WAREHOUSE_case1.log -> testing result of case1
   WAREHOUSE_case2.log -> testing result of case2
   WAREHOUSE_case3.log -> testing result of case3
Transportation Model:   
   TRANSPORTATION.log
Preprocessing Model:
   PREPROCESSING.log 
Assembling Model:   
   ASSEMBLING.log
   
   
Model Testing Behavior Analysis

SCOM Model:
   Case1: The system starts as expected. All subcomponents work as expected.

   Case2: The system works as expected. No delay occurs during the whole process. 
   Other aspects of the system are also tested. There is no inventory overflow 
   in the preprocessing model. The scheduling mechanism carried out by the 
   preprocessing model does work.
   (For this case, a tie-breaking problem is solved. Details please refer to the
   SCOM SIMULATION REPORT)


Manufacturer Model:
   The manufacturer model acts as expected. It starts assembling after the first
   half hour, and output the first product after the predefined assembling time. 
   And then it can produce products continuously without delay. The scheduling 
   mechanism does work.


Warehouse Model: 
   Case1: When received 2 units of materials from the outside world via the port
          win1, the Warehouse behaves as expected. It outputs materials every one
          hour (processing_time) through port wout1, and informs outside world 
          that replenishment is needed through port wout2 when the inventory is 
          zero. There is no loss of units in the process.

   Case2: When overflow happens, the warehouse will discard the redundant units,
          and set its inventory to 10 (the predefined maximum capacity). When it
          gets a non-positive input, it will discard the wrong input and keep its
          inventory unchanged. In both cases, information is displayed in the 
          console view.

   Case3: The delivery can be paused by input of ¨C1 either from port win2 or from
          port win3. After the warehouse gets input of 1 from both port win2 and
          port win3, delivery is resumed.


Transportation Model:
   The busy signal is sent at the same time the transportation gets the input 
   from port tin. It outputs 1 to port tout1 and informs the warehouse by an 
   output of 1 through port tout2.


Preprocessing Model:
   The preprocessing model acts as expected. It does preprocessing job silently 
   while waiting for request from the assembling. Upon request, it delivers the 
   finished materials to the assembling without any delay. It also checks the 
   current inventory whenever there is an input from port pin1 or pin2, which 
   would change its inventory, and sends the correct signals to the warehouse 
   after the inventory checking. It delivers materials to the assembling only if
   there is a request form port pin2. The values of before and after variables 
   are maintained correctly during the process.


Assembling Model:
   The assembling model acts properly. After producing one product, it output 1 
   to port aout1, and simultaneously outputs a signal of 1 to the preprocessing 
   via port aout2.