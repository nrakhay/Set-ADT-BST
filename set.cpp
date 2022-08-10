
#include "set.h"

const treenode *find(const treenode *n, const std::string &s)
{
   while (n != nullptr)
   {

      if (n->value == s)
         return n;

      else if (n->value < s)
         n = n->right;

      else
         n = n->left;
   }

   return nullptr;
}

treenode **find(treenode **n, const std::string &s)
{
   while (*n != nullptr)
   {
      if (s == (*n)->value)
         return n;

      else if (s < (*n)->value)
         n = &(*n)->left;

      else if (s > (*n)->value)
         n = &(*n)->right;
   }
   return n;
}

size_t size(const treenode *n)
{
   if (n == nullptr)
      return 0;
   else
      return (1 + size(n->left) + size(n->right));
}

size_t height(const treenode *n)
{
   int depthLeft, depthRight;

   if (n == nullptr)
   {
      return 0;
   }
   else
   {
      depthLeft = height(n->left);
      depthRight = height(n->right);

      if (depthLeft > depthRight)
         return (depthLeft + 1);
      else
         return (depthRight + 1);
   }
}

void deallocate(treenode *n)
{
   if (n == nullptr)
      return;

   deallocate(n->left);
   deallocate(n->right);

   delete n;
}

treenode *makecopy(const treenode *n)
{
   if (n == nullptr)
      return nullptr;

   treenode *copyBegin = new treenode(n->value);
   copyBegin->left = makecopy(n->left);
   copyBegin->right = makecopy(n->right);

   return copyBegin;
}

void print(std::ostream &out, const treenode *n, unsigned int indent)
{
   for (unsigned int i = 0; i != indent; ++i)
      out << "|  ";
   if (n)
   {
      out << (n->value) << "\n";
      print(out, n->left, indent + 1);
      print(out, n->right, indent + 1);
   }
   else
      out << "#\n";
}

// Both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent.

void checkbetween(const treenode *n,
                  const std::string *lowerbound,
                  const std::string *upperbound)
{
   while (n)
   {
      if (lowerbound && *lowerbound >= n->value)
      {
         std::cout << "value " << (n->value);
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         throw std::runtime_error("tree not correct");
      }

      if (upperbound && n->value >= *upperbound)
      {
         std::cout << "value " << (n->value);
         std::cout << "is not below upperbound " << *upperbound << "\n";
         throw std::runtime_error("tree not correct");
      }

      checkbetween(n->left, lowerbound, &(n->value));
      lowerbound = &(n->value);
      n = n->right;
   }
}

unsigned int log_base2(size_t s)
{
   return (s > 1) ? 1 + log_base2(s / 2) : 0;
}

bool set::contains(const std::string &s) const
{
   if (::find(tr, s) == nullptr)
      return false;

   return true;
}

bool set::insert(const std::string &s)
{
   treenode **resFind = ::find(&tr, s);

   if (*resFind == nullptr)
   {
      treenode *nodeToInsert = new treenode(s);
      *resFind = nodeToInsert;

      return true;
   }

   return false;
}

size_t set::size() const
{
   return ::size(tr);
}

size_t set::height() const
{
   return ::height(tr);
}

bool set::empty() const
{
   if ((tr->left == nullptr) && (tr->right == nullptr))
      return true;

   return false;
}

set::~set()
{
   ::deallocate(tr);
}

void set::clear()
{
   ::deallocate(tr);
   tr = nullptr;
}

set::set(const set &other)
{
   tr = ::makecopy(other.tr);
}

set &set::operator=(const set &other)
{
   if (this != &other)
   {
      ::deallocate(tr);

      tr = ::makecopy(other.tr);
   }

   return *this;
}

void set::checksorted() const
{
   ::checkbetween(tr, nullptr, nullptr);
}

void set::print(std::ostream &out, unsigned int indent) const
{
   ::print(out, tr, indent);
}
