#include "CVolatility.h"
#include <algorithm>
#include <cctype>

#define TOUPPER(s) std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::toupper(c); } )

double CVolatility::FindData(const std::string& szHtml, const std::string& pair, VOLTYPE vtype)
{
	if (pair.empty()) return -1;
	m_pair = pair;
	TOUPPER(m_pair);
	m_column = vtype;
	GumboOutput* output = gumbo_parse(szHtml.c_str() );
	double res = FindTable(output->root);
	const GumboOptions mGumboDefaultOptions = { &malloc_wrapper, &free_wrapper, NULL, 8, false, -1, GUMBO_TAG_LAST, GUMBO_NAMESPACE_HTML };
	gumbo_destroy_output(&mGumboDefaultOptions, output);
	return res;
}

double CVolatility::FindTable(GumboNode * node) 
{
    double res = -1;
    if (node->type != GUMBO_NODE_ELEMENT)
    {
        return res;
    }
	GumboAttribute* ptable;
	if ((node->v.element.tag == GUMBO_TAG_TABLE) && (ptable = gumbo_get_attribute(&node->v.element.attributes, "id")) && (m_idtable.compare(ptable->value) == 0))
    {
		GumboVector* children = &node->v.element.children;
		GumboNode* pchild = nullptr;
	    for (unsigned i = 0; i < children->length; ++i)
        {
			pchild = static_cast<GumboNode*>(children->data[i]);
			if (pchild && pchild->v.element.tag == GUMBO_TAG_TBODY)
            {
				return FindTableRow(pchild);
			}
		}
	}
	else
    {
		for (unsigned int i = 0; i < node->v.element.children.length; ++i)
        {
			res = FindTable(static_cast<GumboNode*>(node->v.element.children.data[i]));
			if (res != -1) return res;
		}
	}
	return res;
}

double CVolatility::FindTableRow(GumboNode* node)
{
	std::string szRow = "tr_" + m_pair;
	GumboAttribute* prow = nullptr;
	GumboNode* child_node = nullptr;
	GumboVector* children = &node->v.element.children;
	for (unsigned int i = 0; i < children->length; ++i)
    {
		child_node = static_cast<GumboNode*>(node->v.element.children.data[i]);
		if ((child_node->v.element.tag == GUMBO_TAG_TR) &&
			(prow = gumbo_get_attribute(&child_node->v.element.attributes, "id")) &&
			(szRow.compare(prow->value) == 0))
        {
			return GetVolatility(child_node);
		}
	}
	return -1;
}

double CVolatility::GetVolatility(GumboNode* node)
{
	double res = -1;
	GumboNode* child_node = nullptr;
	GumboVector* children = &node->v.element.children;
	int j = 0;
	for (unsigned int i = 0; i < children->length; ++i)
    {
		child_node = static_cast<GumboNode*>(node->v.element.children.data[i]);
		if (child_node->v.element.tag == GUMBO_TAG_TD && j++ == (int)m_column)
        {
			GumboNode* ch = static_cast<GumboNode*>(child_node->v.element.children.data[0]);
			std::string t{ ch->v.text.text };
			std::replace(t.begin(), t.end(), ',', '.');
			res = std::stod(t);
			break;
		}
	}
	return res;
}
