/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.brave.bytecode;

import org.objectweb.asm.ClassVisitor;

public class BraveExternalNavigationHandlerClassAdapter extends BraveClassVisitor {

    static String sBraveExternalNavigationHandlerClassName =
            "org/chromium/chrome/browser/externalnav/BraveExternalNavigationHandler";

    static String sExternalNavigationHandlerClassName =
            "org/chromium/components/external_intents/ExternalNavigationHandler";

    static String sMethodClobberCurrentTabWithFallbackUrl =
            "clobberCurrentTabWithFallbackUrl";

    public BraveExternalNavigationHandlerClassAdapter(ClassVisitor visitor) {
        super(visitor);

        deleteMethod(sBraveExternalNavigationHandlerClassName,
                     sMethodClobberCurrentTabWithFallbackUrl);
        makePublicMethod(sExternalNavigationHandlerClassName,
                         sMethodClobberCurrentTabWithFallbackUrl);
    }
}
