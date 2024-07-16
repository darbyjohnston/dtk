# SPDX-License-Identifier: BSD-3-Clause
# Copyright (c) 2024 Darby Johnston
# All rights reserved.

import tinygfx.tgCore as tg

import unittest

class VectorTest(unittest.TestCase):

    def test_members(self):
        v2 = tg.V2I()
        self.assertEqual(v2[0], 0)
        self.assertEqual(v2[1], 0)
        v3 = tg.V3F()
        self.assertEqual(v3[0], 0)
        self.assertEqual(v3[1], 0)
        self.assertEqual(v3[2], 0)
        v4 = tg.V4F()
        self.assertEqual(v4[0], 0)
        self.assertEqual(v4[1], 0)
        self.assertEqual(v4[2], 0)
        self.assertEqual(v4[3], 0)
        
        v2 = tg.V2I()
        v2[0] = 1
        v2[1] = 2
        self.assertEqual(v2[0], 1)
        self.assertEqual(v2[1], 2)
        v3 = tg.V3F()
        v3[0] = 1
        v3[1] = 2
        v3[2] = 3
        self.assertEqual(v3[0], 1)
        self.assertEqual(v3[1], 2)
        self.assertEqual(v3[2], 3)
        v4 = tg.V4F()
        v4[0] = 1
        v4[1] = 2
        v4[2] = 3
        v4[3] = 4
        self.assertEqual(v4[0], 1)
        self.assertEqual(v4[1], 2)
        self.assertEqual(v4[2], 3)
        self.assertEqual(v4[3], 4)
        
        v2 = tg.V2I(1, 2)
        self.assertEqual(v2.x, 1)
        self.assertEqual(v2.y, 2)
        v3 = tg.V3F(1, 2, 3)
        self.assertEqual(v3.x, 1)
        self.assertEqual(v3.y, 2)
        self.assertEqual(v3.z, 3)
        v4 = tg.V4F(1, 2, 3, 4)
        self.assertEqual(v4.x, 1)
        self.assertEqual(v4.y, 2)
        self.assertEqual(v4.z, 3)
        self.assertEqual(v4.w, 4)
        
        v2 = tg.V2I()
        v2.x = 1;
        v2.y = 2;
        self.assertEqual(v2.x, 1)
        self.assertEqual(v2.y, 2)
        v3 = tg.V3F()
        v3.x = 1
        v3.y = 2
        v3.z = 3
        self.assertEqual(v3.x, 1)
        self.assertEqual(v3.y, 2)
        self.assertEqual(v3.z, 3)
        v4 = tg.V4F()
        v4.x = 1
        v4.y = 2
        v4.z = 3
        v4.w = 4
        self.assertEqual(v4.x, 1)
        self.assertEqual(v4.y, 2)
        self.assertEqual(v4.z, 3)
        self.assertEqual(v4.w, 4)

    def test_functions(self):
        l = tg.length(tg.V2F(0, 1))
        self.assertEqual(1, l)
        l = tg.length(tg.V2F(1, 0))
        self.assertEqual(1, l)
        
        v = tg.normalize(tg.V2F(0, 2))
        self.assertEqual(tg.length(v), 1)
        v = tg.normalize(tg.V2F(2, 0))
        self.assertEqual(tg.length(v), 1)
        
        d = tg.dot(tg.V2F(0, 1), tg.V2F(1, 0))
        self.assertEqual(0, d)
        d = tg.dot(tg.V2F(0, 1), tg.V2F(0, -1))
        self.assertEqual(-1, d)
        
        v = tg.perpCW(tg.V2F(1, 0))
        self.assertEqual(tg.V2F(0, -1), v)
        v = tg.perpCCW(tg.V2F(1, 0))
        self.assertEqual(tg.V2F(0, 1), v)

    def test_operators(self):
        v = tg.V2F(1, 2) + tg.V2F(3, 4)
        self.assertEqual(tg.V2F(4, 6), v)
        v = tg.V2F(1, 2) + 1
        self.assertEqual(tg.V2F(2, 3), v)

        v = tg.V2F(3, 4) - tg.V2F(1, 2)
        self.assertEqual(tg.V2F(2, 2), v)
        v = tg.V2F(3, 4) - 1
        self.assertEqual(tg.V2F(2, 3), v)
        
        self.assertEqual(tg.V2F(1, 2), tg.V2F(1, 2))
        self.assertNotEqual(tg.V2F(1, 2), tg.V2F(2, 1))
