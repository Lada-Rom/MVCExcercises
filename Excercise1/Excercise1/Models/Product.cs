using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Excercise1.Models
{
    public class Product
    {
        public int ID { get; set;}
        public string Name { get; set;}
        public decimal Price { get; set;}
        public string Description { get; set;}

        public Product(int id, string name, decimal price, string description)
        { 
            ID = id;
            Name = name;
            Price = price;
            Description = description;
        }

        public Product()
        {
            // TODO: Complete member initialization
        }
    }
}