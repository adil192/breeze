#include <KColorScheme>
#include <KConfig>
#include <KConfigGroup>

#include <QDebug>

int main(int, char **)
{
    KConfig globals("kdeglobals");
    KConfigGroup general(&globals, QStringLiteral("General"));
    if (general.readEntry("ColorScheme") != QLatin1String("Areeze")) {
        return 0;
    }
    QString areezeLightPath = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("color-schemes/AreezeLight.colors"));
    if (areezeLightPath.isEmpty()) {
        return 0;
    }
    KConfig areezeLight(areezeLightPath, KConfig::SimpleConfig);
    for (const auto &group : areezeLight.groupList()) {
        auto destination = KConfigGroup(&globals, group);
        KConfigGroup(&areezeLight, group).copyTo(&destination, KConfig::Notify);
    }
    return 0;
}
