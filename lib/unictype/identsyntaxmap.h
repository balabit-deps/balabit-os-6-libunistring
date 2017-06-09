/* Three-level bitmap lookup.
   Copyright (C) 2000-2002, 2005-2007, 2009-2010 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2000-2002.

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

static inline int identsyntax_lookup (ucs4_t uc);

static inline int
identsyntax_lookup (ucs4_t uc)
{
  unsigned int index1 = uc >> identsyntax_header_0;
  if (index1 < identsyntax_header_1)
    {
      int lookup1 = TABLE.level1[index1];
      if (lookup1 >= 0)
        {
          unsigned int index2 = (uc >> identsyntax_header_2) & identsyntax_header_3;
          int lookup2 = TABLE.level2[lookup1 + index2];
          if (lookup2 >= 0)
            {
              unsigned int index3 = (uc & identsyntax_header_4) + lookup2;
              /* level3 contains 2-bit values.  */
              unsigned int lookup3 = TABLE.level3[index3 >> 3];

              return (lookup3 >> (2 * (index3 & 7))) & 3;
            }
        }
    }
  return UC_IDENTIFIER_INVALID;
}
