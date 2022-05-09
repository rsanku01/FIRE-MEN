//SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.5.0 <0.8.0;

contract AlarmRegistry {

uint idDigits = 16;
uint idModulus = 10 ** idDigits;



struct FireMen {
    string _UserID;
    uint _Flame;
    uint _Electric;
    uint _Gas;
    uint _timestmp;
}

FireMen[] public Registry;

function _generateId(string memory _str) private view returns (uint) {
    uint rand = uint(keccak256(abi.encodePacked(_str)));
    return rand% idModulus;
}
function  ClassofFire(string memory _UserID, uint _Flame, uint _Electric, uint _Gas)public{   
     uint randId = _generateId(_UserID); 
        _registerAction(_UserID,_Flame,_Electric,_Gas);
        SensorValue1[randId] = _Flame;
        SensorValue2[randId] = _Electric;
        SensorValue3[randId] = _Gas;
        CheckingSensorValues(randId);
}



function CheckingSensorValues(uint _values) private view
 SensorValues(1,0,0,_values)  {}

    mapping (uint => uint) private SensorValue1;

    mapping (uint => uint) private SensorValue2; 

    mapping (uint => uint) private SensorValue3;
    
    modifier SensorValues (uint _Flame, uint _Electric, uint _Gas, uint _values) {
         require(SensorValue1[_values]  == 1,"Flame Must be Detected");
         require (SensorValue2[_values] <= 1,"Digital Output of Electrical Connectivity");
         require (SensorValue3[_values] <= 1,"Digital Output of Gas Sensor");

    // NOTE:
         /*if (SensorValue1[_values] == 1){
          if (SensorValue2[_values] == 1) {
            revert("Electric Fire - Class_C Fire");
            }
          else if (SensorValue3[_values]  == 1) {
            revert("Gas Fire - Class_B Fire");
          }
        }
        else
        {
            revert("Other Fire - Class_A Fire");
        }*/
        _;
    }/*
    function Time_call() public view returns (uint256) {
    uint timestmp = block.timestamp;
    return timestmp;
    }*/
    event registerAction(uint SensorValue_1, uint SensorValue_2, uint SensorValue_3,uint Time);

    function _registerAction(string memory _UserID, uint _Flame, uint _Electric, uint _Gas) private {
    Registry.push(FireMen(_UserID, _Flame, _Electric, _Gas, block.timestamp));
    emit registerAction(msg.value, msg.value, msg.value, block.timestamp);
}
      
}