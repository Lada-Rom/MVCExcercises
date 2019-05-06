using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Excercise3.Models
{
    public class Product
    {
        public int ID { get; set; }
        public string Name { get; set; }
        public decimal Price { get; set; }
        public DateTime CreatedDate { get; set; }
    }
}