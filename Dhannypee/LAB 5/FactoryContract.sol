//SPDX-License-Identifier: GPL-3.0
//Exercise 1
pragma solidity >=0.5 < 0.8;
contract Factory{
//Exercise 2
    uint idDigits = 16;
//Exercise 3
   uint idModulus = 10^idDigits;
//Exercise 4
   struct Product
   {
       string name;
       uint id;
   }
//Exercise 5
   Product[] public products;
  /* event NewProduct(uint ArrayProductId, string name, uint id);
//Exercise 6
   function _createProduct(string memory _name, uint _id) private{ 
       products.push(Product(_name, _id));
   uint ArrayProduct = products.length-1;
   emit NewProduct(ArrayProductId, _name, _id);
   }*/
//Exercise 7
   function _generateRandomld(string memory _str) private view 
   returns (uint){
//Exercise 8
      uint rand = uint(keccak256(abi.encodePacked(_str))); 
      return rand%idModulus; 
   }
    function _createRandomProduct(string memory _name) public 
    {
        uint randId = _generateRandomld(_name);
        _createProduct(_name,randId);
        
    }
//Exercise 9
        event NewProduct(uint ArrayProductId, string name, uint id);
   function _createProduct(string memory _name, uint _id) 
   private{
       products.push(Product(_name, _id));
   uint ArrayProductId = products.length-1;
   emit NewProduct(ArrayProductId, _name, _id);
   }
//Exercise 10
   mapping (uint => address) public productToOwner;
   mapping (address => uint) OwnerProductCount;
   
//Exercise 11
    function Ownership (uint ArrayProductId) private {
    productToOwner[ArrayProductId] = msg.sender;
    OwnerProductCount[msg.sender]++;
       
   }
//Exercise 12
  function getProductsByOwner (address _owner) external view 
   returns(uint[] memory) {
     uint counter = 0;
     uint array = OwnerProductCount[_owner];
    uint[] memory result = new uint[] (array);
    for (uint i = 0; i< products.length; i++) {
       if (productToOwner[i]== _owner){
         result[counter]= i;
         counter++;
       }
    }
     return result;
   }
//Exercise 13  Check Safe Remote Purchase File

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
