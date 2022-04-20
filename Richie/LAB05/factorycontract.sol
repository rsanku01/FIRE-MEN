//SPDX-License-Identifier: GPL-3.0
//Excercise 1
pragma solidity >=0.5.0 <0.8.0;
contract Factory{
//Exercise 2    
    uint idDigits = 16;
//Exercise 3    
    uint idModulus = 10**idDigits;
//Exercise 4    
    struct Product {
        string name;
        uint id;
    }
//Exercise 5    
    Product[] public products;
        /*function _createProduct(string memory _name, uint _id)
    private{ 
        products.push(Product(_name, _id));
        event NewProduct(uint ArrayProductId, string name, uint id);
        array.push()

    }*/

    //mapping(address => uint) productToOwner;
    
//Exercise 7
    function _generateRandomId(string memory _str)private view 
    returns (uint){
//Exercise 8        
        uint rand = uint(keccak256(abi.encodePacked(_str)));
        return rand%idModulus;
         

    }
//Exercise 6    
    function  createRandomProduct(string memory _name)public{        
        uint randId = _generateRandomId(_name);
        _createProduct(_name,randId);
              
    }    
////Exercise 9
    event NewProduct(uint ArrayProductId, string name, uint id);
   

 function _createProduct(string memory _name, uint _id)
    private{ 
       products.push(Product(_name, _id));
      uint ArrayProductId = products.length-1;
      emit NewProduct(ArrayProductId, _name, _id);
       productToOwner[ArrayProductId] = msg.sender;

    
    }
//Exercise 10    
     mapping(uint => address) productToOwner;
     mapping(address => uint) ownerProductCount;
////Exercise 11
    function Ownership(uint ArrayProductId) public  returns (address) {
        //productToOwner[ArrayProductId] = msg.sender;    
        
        ownerProductCount[msg.sender]++;
        return productToOwner[ArrayProductId];
        
        }
//Exercise 12          

    function getProductsByOwner (address _owner) external view 
   returns(uint[] memory) {
     uint counter = 0;
     uint array = ownerProductCount[_owner];
    uint[] memory result = new uint[] (array);
    for (uint i = 0; i< products.length; i++) {
       if (productToOwner[i]== _owner){
         result[counter]= i;
         counter++;
       }
        }
     return result;

   }
//Exercise 13

//Exercise 14   
    mapping (uint => uint) public age;
    modifier olderThan (uint _age, uint _userId)
    {
      require( _userId >= _age );
              _;

    }
    function validationUsers( uint _userId) public view olderThan(18,_userId) {

    }

}
