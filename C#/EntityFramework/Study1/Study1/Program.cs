using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.Entity;

namespace Study1
{
    class Cat
    {
        int id;
        string name;
        int age;
        public Cat() { }
        public int Id
        {
            get { return id; }
            set { id = value; }
        }
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        public int Age
        {
            get { return age; }
            set { age = value; }
        }
    }
    class UserContext : DbContext
    {
        DbSet<Cat> cats;
        public UserContext() : base("DBConnection") { }
        public DbSet<Cat> Cats => cats;
    }
    class Program
    {
        static void Main(string[] args)
        {
            Cat[] cats = new Cat[4] { new Cat() { Name = "Pussy", Age = 4 },
             new Cat() { Name = "Rolly", Age = 7 },
             new Cat() { Name = "Molly", Age = 2 },
             new Cat() { Name = "Ozzy", Age = 11 }};
            using (UserContext db = new UserContext())
            {
                for (int i = 0; i < 4; i++)
                {
                    db.Cats.Add(cats[i]);
                }
                db.SaveChanges();
                Console.WriteLine("Done!");

                var catsFromDb = db.Cats;
                Console.WriteLine();
                foreach (Cat u in catsFromDb)
                {
                    Console.WriteLine("{0}.{1} - {2}", u.Id, u.Name, u.Age);
                }
            }
            Console.ReadLine();

        }
    }
}
